#include "renderer2d.h"

namespace dream
{
	namespace graphics
	{
#pragma region SimpleRenderer2D
		/*void Renderer2D::Submit(const IRenderable2D * renderable)
		{
			m_RenderQueue.push_back((StaticSprite*)(renderable));
		}

		void Renderer2D::Flush()
		{
			while (!m_RenderQueue.empty())
			{
				const StaticSprite* renderable = m_RenderQueue.front();
				renderable->GetVAO()->Bind();
				renderable->GetIBO()->Bind();

				Vector3 pos = renderable->GetPosition();
				renderable->GetShader().SetUniformMat4("ml_matrix", maths::Mat4x4::Translation(pos));
				glDrawElements(GL_TRIANGLES, renderable->GetIBO()->GetCount(), GL_UNSIGNED_SHORT, nullptr);

				renderable->GetIBO()->Unbind();
				renderable->GetVAO()->Unbind();

				m_RenderQueue.pop_front();
			}
		}*/
#pragma endregion

#pragma region BatchRenderer2D
		//
		//BatchRenderer2D::BatchRenderer2D()
		//{
		//	Init();
		//}

		//BatchRenderer2D::~BatchRenderer2D()
		//{
		//	delete m_IBO;
		//	glDeleteBuffers(1, &m_VBO);
		//}

		//void BatchRenderer2D::Begin()
		//{
		//	glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
		//	m_buffer = (VertexData*)glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY);
		//}

		//void BatchRenderer2D::Submit(const IRenderable2D * renderable)
		//{
		//	const Vector3& position = renderable->GetPosition();
		//	const Vector2& size = renderable->GetSize();
		//	const Vector4& color = renderable->GetColor();

		//	int r = color.m_X * 255.0f;
		//	int g = color.m_Y * 255.0f;
		//	int b = color.m_Z * 255.0f;
		//	int a = color.m_W * 255.0f;

		//	unsigned int channel = a << 24 | b << 16 | g << 8 | r;

		//	m_buffer->vertex = *m_transformationBack * position;
		//	m_buffer->color = channel;
		//	m_buffer++;

		//	m_buffer->vertex = *m_transformationBack * Vector3(position.m_X, position.m_Y + size.m_Y, position.m_Z);
		//	m_buffer->color = channel;
		//	m_buffer++;

		//	m_buffer->vertex = *m_transformationBack * Vector3(position.m_X + size.m_X, position.m_Y + size.m_Y, position.m_Z);
		//	m_buffer->color = channel;
		//	m_buffer++;

		//	m_buffer->vertex = *m_transformationBack * Vector3(position.m_X + size.m_X, position.m_Y, position.m_Z);
		//	m_buffer->color = channel;
		//	m_buffer++;

		//	m_indexCount += 6;
		//}

		//void BatchRenderer2D::End()
		//{
		//	glUnmapBuffer(GL_ARRAY_BUFFER);
		//	glBindBuffer(GL_ARRAY_BUFFER, 0);
		//}

		//void BatchRenderer2D::Flush()
		//{
		//	glBindVertexArray(m_VAO);
		//	m_IBO->Bind();

		//	//glDrawElements(GL_TRIANGLES, m_indexCount, GL_UNSIGNED_SHORT, NULL);
		//	glDrawElements(GL_TRIANGLES, m_indexCount, GL_UNSIGNED_INT, NULL);

		//	m_IBO->Unbind();
		//	glBindVertexArray(0);
		//	m_indexCount = 0;
		//}

		//void BatchRenderer2D::Init()
		//{
		//	glGenVertexArrays(1, &m_VAO);
		//	glGenBuffers(1, &m_VBO);

		//	glBindVertexArray(m_VAO);
		//	glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
		//	glBufferData(GL_ARRAY_BUFFER, RENDERER_BUFFER_SIZE, NULL, GL_DYNAMIC_DRAW);
		//	glEnableVertexAttribArray(SHADER_VERTEX_INDEX);
		//	glEnableVertexAttribArray(SHADER_COLOR_INDEX);
		//	glVertexAttribPointer(SHADER_VERTEX_INDEX, 3, GL_FLOAT, GL_FALSE, RENDERER_VERTEX_SIZE, (const GLvoid*)0);
		//	glVertexAttribPointer(SHADER_COLOR_INDEX, 4, GL_UNSIGNED_BYTE, GL_TRUE, RENDERER_VERTEX_SIZE, (const GLvoid*)(offsetof(VertexData, VertexData::color)));
		//	glBindBuffer(GL_ARRAY_BUFFER, 0);

		//	//GLushort indicies[RENDERER_INDICIES_SIZE];
		//	GLuint* indicies = new GLuint[RENDERER_INDICIES_SIZE];

		//	//short offset = 0;
		//	int offset = 0;
		//	for (unsigned /*short*/ int i = 0; i < RENDERER_INDICIES_SIZE; i += 6)
		//	{
		//		indicies[  i  ] = offset + 0;
		//		indicies[i + 1] = offset + 1;
		//		indicies[i + 2] = offset + 2;

		//		indicies[i + 3] = offset + 2;
		//		indicies[i + 4] = offset + 3;
		//		indicies[i + 5] = offset + 0;

		//		offset += 4;
		//	}

		//	m_IBO = new IndexBuffer(indicies, RENDERER_INDICIES_SIZE);

		//	glBindVertexArray(0);
		//} 

#pragma endregion
	
	}
}