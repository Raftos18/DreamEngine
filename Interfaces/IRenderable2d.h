#pragma once
#include "./IRenderer2d.h"

#include "../Math/maths.h"
#include "../Graphics/texture.h"
#include "../Graphics/Buffers/arrayBuffer.h"
#include "../Graphics/Buffers/ElementBuffer.h"
#include "../Graphics/Buffers/vertexArray.h"
#include "../Graphics/Shaders/shader.h"

namespace dream
{
	namespace graphics
	{	
		// This should be implemented by any 2D object that wants to be drawn.
		class IRenderable2D
		{
		public:
			maths::Vector3 m_Position;
			maths::Vector2 m_Size;
			unsigned int m_Color;
			std::vector<maths::Vector2> m_UV;
			Texture* m_Texture;

			IRenderable2D() : m_Texture(nullptr)
			{
				SetUVDefaults();
			};

		public:
			IRenderable2D(maths::Vector3 pos, maths::Vector2 size, unsigned int color):
				m_Position(pos), m_Size(size), m_Color(color), m_Texture(nullptr)
			{
				SetUVDefaults();
			};

			virtual void Submit(IRenderer2D* renderer) const
			{
				renderer->Submit(this);
			}

			void SetColor(unsigned int color) { m_Color = color; }
			void SetColor(maths::Vector4& color)
			{
				int r = color.m_X * 255.0f;
				int g = color.m_Y * 255.0f;
				int b = color.m_Z * 255.0f;
				int a = color.m_W * 255.0f;

				m_Color = a << 24 | b << 16 | g << 8 | r;
			}

			inline const maths::Vector3& GetPosition() const { return m_Position; }
			inline const maths::Vector2& GetSize() const { return m_Size; }
			inline const unsigned int GetColor() const { return m_Color; }
			inline const std::vector<maths::Vector2>& GetUV() const { return m_UV; }
			inline const GLuint getTID() const { return m_Texture == nullptr ? 0 : m_Texture->GetTextID();}

		private:
			void SetUVDefaults() 
			{
				m_UV.push_back(maths::Vector2(0, 0));
				m_UV.push_back(maths::Vector2(0, 1));
				m_UV.push_back(maths::Vector2(1, 1));
				m_UV.push_back(maths::Vector2(1, 0));
			}
		};
	}
}



