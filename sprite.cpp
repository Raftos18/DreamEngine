#include "sprite.h"

namespace dream
{
	namespace graphics
	{
		// Sprite
		Sprite::Sprite(float x, float y, float width, float height, Vector4 & color) :
			IRenderable2D(Vector3(x, y, 0), Vector2(width, height), color)
		{

		}

		// Static-Sprite

		StaticSprite::StaticSprite(float x, float y, float width, float height, Vector4& color, Shader& shader):
			IRenderable2D(Vector3(x,y,0), Vector2(width, height), color), m_Shader(shader)
		{
			m_VertexArray = new VertexArray();
			GLfloat vertices[]
			{
				0, 0, 0,
				0, height, 0,
				width, height, 0,
				width, 0, 0,
			};

			GLfloat colors[]
			{
				color.GetX(), color.GetY(), color.GetZ(), color.GetW(),
				color.GetX(), color.GetY(), color.GetZ(), color.GetW(),
				color.GetX(), color.GetY(), color.GetZ(), color.GetW(),
				color.GetX(), color.GetY(), color.GetZ(), color.GetW(),
			};

			m_VertexArray->AddBuffer(new Buffer(vertices, 4 * 3, 3), 0);
			m_VertexArray->AddBuffer(new Buffer(colors, 4 * 4, 4), 1);


			GLushort indices[]{ 0,1,2,2,3,0 };
			m_IndexBuffer = new IndexBuffer(indices, 6);
		}
		StaticSprite::~StaticSprite()
		{
			delete m_VertexArray;
			delete m_IndexBuffer;
		}
		
	}
}

