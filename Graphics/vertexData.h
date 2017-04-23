#pragma once
// Include GLEW
#include <GL\glew.h>
// Include Dream
#include "../Math/maths.h"

namespace dream {
	namespace graphics {

		struct VertexData
		{
			maths::Vector3 vertex;			
			maths::Vector2 textCoord;		// TexCoord
			float textureId;				// Texture ID
			unsigned int color;				// Color of the vertex

			inline void Submit(maths::Vector3 vert, maths::Vector2 uv, float textId, unsigned int col) 
			{
				vertex = vert;
				textCoord = uv;
				textureId = textId;
				color = col;
			}

			// Returns a pointer to a VertexData buffer mapped to OpenGL
			static inline VertexData* MapBuffer() 
			{
				return (VertexData*)glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY);
			}			

			// Unmaps the current buffer
			static inline void UnmapBuffer() 
			{
				glUnmapBuffer(GL_ARRAY_BUFFER);
			}
		};
	}
}