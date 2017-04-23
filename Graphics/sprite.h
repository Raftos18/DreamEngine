#pragma once

#include "../Interfaces/IRenderable2d.h"

namespace dream
{
	namespace graphics
	{
		class Sprite : public IRenderable2D
		{			
		public:
			maths::Vector3& Position;
		public:
			Sprite(float x, float y, float width, float height, unsigned int color);
			Sprite(float x, float y, float width, float height, Texture* texture);
		};	
	} 
}
