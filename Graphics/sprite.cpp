#include "sprite.h"

namespace dream
{
	namespace graphics
	{
		// Sprite
		Sprite::Sprite(float x, float y, float width, float height, unsigned int color) :
			IRenderable2D(maths::Vector3(x, y, 0), maths::Vector2(width, height), color), Position(m_Position)
		{
		}

		Sprite::Sprite(float x, float y, float width, float height, Texture * texture) :
			IRenderable2D(maths::Vector3(x, y, 0), maths::Vector2(width, height), 0xffddffdd), Position(m_Position)
		{
			m_Texture = texture;
		}			
	}
}

