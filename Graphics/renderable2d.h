#pragma once
#include "renderer2d.h"

#include "Graphics\texture.h"
#include "Graphics\Buffers\buffer.h"
#include "Graphics\Buffers\indexBuffer.h"
#include "Graphics\Buffers\vertexArray.h"
#include "Math\maths.h"
#include "Graphics\Shaders\Shader.h"

namespace dream
{
	namespace graphics
	{
		using namespace maths;
		struct VertexData
		{						
			Vector3 vertex;	
			Vector2 uv;				// TexCoord
			float tid;				// Texture ID
			unsigned int color;
		};

		// This should be implemented by any 2D object that wants to be drawn.
		class IRenderable2D
		{
		protected:
			Vector3 m_Position;
			Vector2 m_Size;
			Vector4 m_Color;
			std::vector<Vector2> m_UV;
			Texture* m_Texture;

			IRenderable2D() : m_Texture(nullptr)
			{
				SetUVDefaults();
			};

		public:
			IRenderable2D(Vector3 pos, Vector2 size, Vector4 color):
				m_Position(pos), m_Size(size), m_Color(color), m_Texture(nullptr)
			{
				SetUVDefaults();
			};

			virtual void Submit(IRenderer2D* renderer) const
			{
				renderer->Submit(this);
			}

			inline const Vector3& GetPosition() const { return m_Position; }
			inline const Vector2& GetSize() const { return m_Size; }
			inline const Vector4& GetColor() const { return m_Color; }
			inline const std::vector<Vector2>& GetUV() const { return m_UV; }
			inline const GLuint getTID() const { return m_Texture == nullptr ? 0 : m_Texture->GetTextID();}

		private:
			void SetUVDefaults() 
			{
				m_UV.push_back(Vector2(0, 0));
				m_UV.push_back(Vector2(0, 1));
				m_UV.push_back(Vector2(1, 1));
				m_UV.push_back(Vector2(1, 0));
			}
		};
	}
}



