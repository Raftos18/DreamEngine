#pragma once
// FreeType
#include <ft2build.h>
#include FT_FREETYPE_H
// Std. 
#include <map>

// Dream
#include "renderable2d.h"

namespace dream {
	namespace graphics {

		// Make this work properly with color from base class
		class Label : public IRenderable2D
		{
		private:
			std::string					m_Text;						
			GLfloat						m_Scale;

			// REFACTOR
			maths::Vector3				Color;
		
		public:			
			Label(const std::string text, maths::Vector2 position, GLfloat scale, maths::Vector3 color);
			~Label() {};

			void Submit(IRenderer2D* renderer) const override;					
		};
	}
}