#pragma once
#include "renderer2d.h"

#include "buffer.h"
#include "indexBuffer.h"
#include "vertexArray.h"
#include "Shader.h"
#include "maths.h"

namespace dream
{
	namespace graphics
	{
		using namespace maths;
		struct VertexData
		{						
			Vector3 vertex;	
			Vector2 uv;		// TexCoord
			//unsigned int tid;		
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

			IRenderable2D() 
			{
				SetUVDefaults();
			};

		public:
			IRenderable2D(Vector3 pos, Vector2 size, Vector4 color):
				m_Position(pos), m_Size(size), m_Color(color)
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



