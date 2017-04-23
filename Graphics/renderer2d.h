#pragma once
// Freetype
#include <ft2build.h>
// Dream
#include "../Interfaces/IRenderer2d.h"
#include "../Interfaces/IRenderable2d.h"
#include "sprite.h"
#include "label.h"

namespace dream
{
	namespace graphics
	{
		static const int RENDERER_MAX_SPRITES = 60000;
		static const int RENDERER_VERTEX_SIZE = sizeof(VertexData);
		static const int RENDERER_SPRITE_SIZE = RENDERER_VERTEX_SIZE * 4;
		static const int RENDERER_BUFFER_SIZE = RENDERER_SPRITE_SIZE * RENDERER_MAX_SPRITES;
		static const int RENDERER_INDICIES_SIZE = RENDERER_MAX_SPRITES * 6;
		static const int RENDERER_MAX_TEXTURES = 32;

		static const int SHADER_VERTEX_INDEX = 0;
		static const int SHADER_UV_INDEX = 1;
		static const int SHADER_TID_INDEX = 2;
		static const int SHADER_COLOR_INDEX = 3;

		class BatchRenderer2D : public IRenderer2D
		{
		protected:
			GLuint m_VAO;
			GLuint m_VBO;
		    VertexData* m_buffer;
			ElementBuffer* m_EBO;
			GLsizei m_indexCount;

			std::vector<GLuint> m_TextureSlots;						

		public:
			BatchRenderer2D();
			~BatchRenderer2D();

			void Begin() override;
			void Submit(const IRenderable2D* renderable)  override;		
			void End() override;
			void Flush() override;

		protected:
			virtual void Init();			
		};
	}
}

