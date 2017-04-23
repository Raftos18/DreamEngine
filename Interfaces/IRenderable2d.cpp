#include "IRenderable2d.h"

namespace dream {
	namespace graphics {

		IRenderable2D::IRenderable2D() : m_Texture(nullptr)
		{
			SetUVDefaults();
		};

		IRenderable2D::IRenderable2D(maths::Vector3 pos, maths::Vector2 size, unsigned int color) :
			m_Position(pos), m_Size(size), m_Color(color), m_Texture(nullptr)
		{
			SetUVDefaults();
		};

		void IRenderable2D::Submit(IRenderer2D* renderer) const
		{
			renderer->Submit(this);
		}

		void IRenderable2D::SetColor(unsigned int color)
		{
			m_Color = color;
		}

		void IRenderable2D::SetColor(maths::Vector4& color)
		{
			int r = color.m_X * 255.0f;
			int g = color.m_Y * 255.0f;
			int b = color.m_Z * 255.0f;
			int a = color.m_W * 255.0f;

			m_Color = a << 24 | b << 16 | g << 8 | r;
		}

		void IRenderable2D::SetUVDefaults()
		{
			m_UV.push_back(maths::Vector2(0, 0));
			m_UV.push_back(maths::Vector2(0, 1));
			m_UV.push_back(maths::Vector2(1, 1));
			m_UV.push_back(maths::Vector2(1, 0));
		}
	}
}
