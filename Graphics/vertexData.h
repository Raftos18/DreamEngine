#pragma once
// Include Dream
#include "../Math/maths.h"

namespace dream {
	namespace graphics {

		struct VertexData
		{
			maths::Vector3 vertex;			
			maths::Vector2 uv;				// TexCoord
			float tid;						// Texture ID
			unsigned int color;				// Color of the vertex
		};
	}
}