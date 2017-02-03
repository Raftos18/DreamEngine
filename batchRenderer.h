#pragma once
#include "renderable2d.h"
#include "sprite.h"

namespace dream
{
	namespace graphics
	{
		class BatchRenderer2D : public IRenderer2D
		{
		private:
			GLuint m_VAO;
			GLuint m_VBO;
			VertexData* m_buffer;
			IndexBuffer* m_IBO;
			GLsizei m_indexCount;

		public:
			BatchRenderer2D();
			~BatchRenderer2D();

			void Begin() override;
			void Submit(const IRenderable2D* renderable)  override;
			void End() override;
			void Flush() override;
		private:
			void Init();
		};
	}
}

