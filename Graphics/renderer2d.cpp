#include "renderer2d.h"
#include "textureManager.h"

namespace dream {
	namespace graphics {

		Renderer2D::Renderer2D() :
			m_VBO(new ArrayBuffer(NULL, RENDERER_BUFFER_SIZE, GL_DYNAMIC_DRAW)),
			m_VAO(new VertexArray())
		{
			Init();
		}

		Renderer2D::~Renderer2D()
		{
			delete m_EBO;
			delete m_VAO;
			delete m_VBO;
			delete m_indices;
		}

		void Renderer2D::Init()
		{
			m_VAO->Bind();
			m_VBO->Bind();

			// Tell OpenGL to enable the generic vertex attribute array specified by index
			// and use the currently bound VAO for the operations
			glEnableVertexAttribArray(SHADER_VERTEX_INDEX);
			glEnableVertexAttribArray(SHADER_UV_INDEX);
			glEnableVertexAttribArray(SHADER_TID_INDEX);
			glEnableVertexAttribArray(SHADER_COLOR_INDEX);

			// Specify the location and data format of the array of generic vertex attributes at index "index" to use when rendering
			glVertexAttribPointer(SHADER_VERTEX_INDEX, 3, GL_FLOAT, GL_FALSE, RENDERER_VERTEX_SIZE, (const GLvoid*)0);
			glVertexAttribPointer(SHADER_UV_INDEX, 2, GL_FLOAT, GL_FALSE, RENDERER_VERTEX_SIZE, (const GLvoid*)(offsetof(VertexData, VertexData::textCoord)));
			glVertexAttribPointer(SHADER_TID_INDEX, 1, GL_FLOAT, GL_FALSE, RENDERER_VERTEX_SIZE, (const GLvoid*)(offsetof(VertexData, VertexData::textureId)));
			glVertexAttribPointer(SHADER_COLOR_INDEX, 4, GL_UNSIGNED_BYTE, GL_TRUE, RENDERER_VERTEX_SIZE, (const GLvoid*)(offsetof(VertexData, VertexData::color)));

			// Unbind buffer object	
			m_VBO->Unbind();			

			// Create indices and save the pointer
			m_indices = ElementBuffer::CreateIndexTriangles(RENDERER_INDICES_SIZE);
			// Create new Element buffer object and pass it the data
			m_EBO = new ElementBuffer(m_indices, RENDERER_INDICES_SIZE);
		
			m_VAO->Unbind();
		}

		inline void Renderer2D::SubmitVertexData(const IRenderable2D * renderable, const float textId)
		{
			const maths::Vector3& position = renderable->GetPosition();
			const maths::Vector2& size = renderable->GetSize();
			const unsigned int color = renderable->GetColor();
			const std::vector<maths::Vector2>& uv = renderable->GetUV();
			
			// Submit data to vertex date object and advance(Mapped to OpenGL)
			m_buffer->Submit(position, uv[0], textId, color);
			m_buffer++;

			// Submit data to vertex date object and advance
			maths::Vector3 tempPos = maths::Vector3(position.m_X, position.m_Y + size.m_Y, position.m_Z);
			m_buffer->Submit(tempPos, uv[1], textId, color);
			m_buffer++;

			// Submit data to vertex date object and advance
			tempPos = maths::Vector3(position.m_X + size.m_X, position.m_Y + size.m_Y, position.m_Z);
			m_buffer->Submit(tempPos, uv[2], textId, color);
			m_buffer++;

			// Submit data to vertex date object and advance
			tempPos = maths::Vector3(position.m_X + size.m_X, position.m_Y, position.m_Z);
			m_buffer->Submit(tempPos, uv[3], textId, color);
			m_buffer++;
		}

		bool Renderer2D::SelectTexture(const IRenderable2D * renderable, float& textId)
		{
			const GLuint tid = renderable->getTextID();			
			// check if renderable has a texture assigned to id
			if (tid > 0) 
			{			
				// Look for textId and if found return true
				for (size_t i = 0; i < m_Textures.size(); i++)
				{
					if (m_Textures[i] == tid)
					{
						textId = (float)(i + 1);
						return true;
					}
				}
			}
			return false;
		}

		bool Renderer2D::AddTexture(const IRenderable2D * renderable, float& textId)
		{
			const GLuint tid = renderable->getTextID();
			if (tid > 0)
			{				
				// If textures saved have reached limit flush renderer
				// and restart adding the new texture. MIGHT CAUSE PERFORMANCE ISSUES
				if (m_Textures.size() >= RENDERER_MAX_TEXTURES)
				{
					Stop();
					Flush();
					Start();
				}
				m_Textures.push_back(tid);
				textId = (float)(m_Textures.size());
				return true;
			}
			return false;
		}

		void Renderer2D::Start()
		{
			// Bind buffer object
			m_VBO->Bind();
			// Map vertex data to OpenGL
			m_buffer = VertexData::MapBuffer();
		}

		void Renderer2D::Submit(const IRenderable2D * renderable)
		{							
			const GLuint tid = renderable->getTextID();			
			float textId = 0.0f;		
			
			// Look for texture or add it if it doen't exist
			if (!SelectTexture(renderable, textId))
				AddTexture(renderable, textId);

			// Submbit data to OpenGL
			SubmitVertexData(renderable, textId);
			
			// Increment indices count
			m_indexCount += 6;
		}

		void Renderer2D::Stop()
		{
			// Unmap vertext data from OpenGL
			VertexData::UnmapBuffer();		
			m_VBO->Unbind();
		}

		void Renderer2D::Flush()
		{		
			// Bind texture array
			TextureManager::Instance().BindTextureArray(&m_Textures);

			// Prepare buffer for rendering
			m_VAO->Bind();
			m_EBO->Bind();

			// ORDER OpenGL to draw
			glDrawElements(GL_TRIANGLES, m_indexCount, GL_UNSIGNED_INT, NULL);

			// Clean things for the next round
			m_EBO->Unbind();
			m_VAO->Unbind();

			m_indexCount = 0;
			m_Textures.clear();
		}
	}
}

