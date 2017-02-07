#include "batchRenderer.h"

dream::graphics::BatchRenderer2D::BatchRenderer2D()
{
	Init();
}

dream::graphics::BatchRenderer2D::~BatchRenderer2D()
{	
	delete m_IBO;
	glDeleteBuffers(1, &m_VBO);
}

void dream::graphics::BatchRenderer2D::Begin()
{
	glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
	m_buffer = (VertexData*)glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY);
}

void dream::graphics::BatchRenderer2D::Submit(const IRenderable2D * renderable)
{
	const Vector3& position = renderable->GetPosition();
	const Vector2& size = renderable->GetSize();
	const Vector4& color = renderable->GetColor();
	const std::vector<Vector2>& uv = renderable->GetUV();
	const GLuint tid = renderable->getTID();

	unsigned int channel = 0;

	float ts = 0.0f;
	if (tid > 0)
	{
		auto found = false;
		for (size_t i = 0; i < m_TextureSlots.size(); i++)
		{
			if (m_TextureSlots[i] == tid)
			{
				ts = (float)(i + 1);
				found = true;
				break;
			}
		}

		if (!found)
		{
			if (m_TextureSlots.size() >= 32) 
			{
				End();
				Flush();
				Begin();
			}
			m_TextureSlots.push_back(tid);
			ts = (float)(m_TextureSlots.size());
		}
	}
	else 
	{
		int r = color.m_X * 255.0f;
		int g = color.m_Y * 255.0f;
		int b = color.m_Z * 255.0f;
		int a = color.m_W * 255.0f;

		channel = a << 24 | b << 16 | g << 8 | r;
	}

	m_buffer->vertex = *m_transformationBack * position;
	m_buffer->uv = uv[0];
	m_buffer->tid = ts;
	m_buffer->color = channel;
	m_buffer++;

	m_buffer->vertex = *m_transformationBack * Vector3(position.m_X, position.m_Y + size.m_Y, position.m_Z);
	m_buffer->uv = uv[1];
	m_buffer->tid = ts;
	m_buffer->color = channel;
	m_buffer++;

	m_buffer->vertex = *m_transformationBack * Vector3(position.m_X + size.m_X, position.m_Y + size.m_Y, position.m_Z);
	m_buffer->uv = uv[2];
	m_buffer->tid = ts;
	m_buffer->color = channel;
	m_buffer++;

	m_buffer->vertex = *m_transformationBack * Vector3(position.m_X + size.m_X, position.m_Y, position.m_Z);
	m_buffer->uv = uv[3];
	m_buffer->tid = ts;
	m_buffer->color = channel;
	m_buffer++;

	m_indexCount += 6;
}

void dream::graphics::BatchRenderer2D::End()
{
	glUnmapBuffer(GL_ARRAY_BUFFER);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void dream::graphics::BatchRenderer2D::Flush()
{
	for (size_t i = 0; i < m_TextureSlots.size(); i++)
	{
		glActiveTexture(GL_TEXTURE0 + i);
		glBindTexture(GL_TEXTURE_2D, m_TextureSlots[i]);
	}

	glBindVertexArray(m_VAO);
	m_IBO->Bind();
	
	glDrawElements(GL_TRIANGLES, m_indexCount, GL_UNSIGNED_INT, NULL);

	m_IBO->Unbind();
	glBindVertexArray(0);
	m_indexCount = 0;
}

void dream::graphics::BatchRenderer2D::Init()
{
	glGenVertexArrays(1, &m_VAO);
	glGenBuffers(1, &m_VBO);

	glBindVertexArray(m_VAO);
	glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
	glBufferData(GL_ARRAY_BUFFER, RENDERER_BUFFER_SIZE, NULL, GL_DYNAMIC_DRAW);

	glEnableVertexAttribArray(SHADER_VERTEX_INDEX);
	glEnableVertexAttribArray(SHADER_UV_INDEX);
	glEnableVertexAttribArray(SHADER_TID_INDEX);
	glEnableVertexAttribArray(SHADER_COLOR_INDEX);

	glVertexAttribPointer(SHADER_VERTEX_INDEX, 3, GL_FLOAT, GL_FALSE, RENDERER_VERTEX_SIZE, (const GLvoid*)0);
	glVertexAttribPointer(SHADER_UV_INDEX, 2, GL_FLOAT, GL_FALSE, RENDERER_VERTEX_SIZE, (const GLvoid*)(offsetof(VertexData, VertexData::uv)));
	glVertexAttribPointer(SHADER_TID_INDEX, 1, GL_FLOAT, GL_FALSE, RENDERER_VERTEX_SIZE, (const GLvoid*)(offsetof(VertexData, VertexData::tid)));
	glVertexAttribPointer(SHADER_COLOR_INDEX, 4, GL_UNSIGNED_BYTE, GL_TRUE, RENDERER_VERTEX_SIZE, (const GLvoid*)(offsetof(VertexData, VertexData::color)));

	glBindBuffer(GL_ARRAY_BUFFER, 0);

	GLuint* indicies = new GLuint[RENDERER_INDICIES_SIZE];
	
	int offset = 0;
	for (unsigned int i = 0; i < RENDERER_INDICIES_SIZE; i += 6)
	{
		indicies[i] = offset + 0;
		indicies[i + 1] = offset + 1;
		indicies[i + 2] = offset + 2;

		indicies[i + 3] = offset + 2;
		indicies[i + 4] = offset + 3;
		indicies[i + 5] = offset + 0;

		offset += 4;
	}

	m_IBO = new IndexBuffer(indicies, RENDERER_INDICIES_SIZE);

	glBindVertexArray(0);
}