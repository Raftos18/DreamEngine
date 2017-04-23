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
		static const int RENDERER_INDICES_SIZE = RENDERER_MAX_SPRITES * 6;
		static const int RENDERER_MAX_TEXTURES = 32;

		static const int SHADER_VERTEX_INDEX = 0;
		static const int SHADER_UV_INDEX = 1;
		static const int SHADER_TID_INDEX = 2;
		static const int SHADER_COLOR_INDEX = 3;

		class Renderer2D : public IRenderer2D
		{

		protected:						
			VertexArray* m_VAO;						// Holds a pointer to a vertex array object
			ArrayBuffer* m_VBO;						// Holds a pointer to a buffer array object
			ElementBuffer* m_EBO;					// Holds a pointer to a element array object

		    VertexData* m_buffer;					// Holds a pointer to a vertex data object
			GLuint* m_indices;						// Holds a reference to the indexed triangle list
			GLsizei m_indexCount;					// Holds the count of indices

			std::vector<GLuint> m_Textures;			// Holds the Texture ids		

		public:
			// Initialises the renderer
			Renderer2D();
			// Deallocates the renderer and its bound objects
			~Renderer2D();

			// Call it before flush
			void Start() override;
			// Use it to assign new Renderables to the Renderer
			void Submit(const IRenderable2D* renderable)  override;		
			// Call it after flush
			void Stop() override;
			// Call it to render an image on screen
			void Flush() override;

		protected:
			// Called in the constructor in order to init renderer
			virtual void Init();			
		private:
			// Submits vertex data to a mapped OpenGL buffer.
		    inline void SubmitVertexData(const IRenderable2D * renderable, const float textId);
			// Selects the texture of a renderable if it can find it in the 	
			inline bool SelectTexture(const IRenderable2D* renderable, float& textId);
			// Adds a new texture to the texture slot. BEWARE this function might cause performance problems
			inline bool AddTexture(const IRenderable2D* renderable, float& textId);
		};
	}
}

