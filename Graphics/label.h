#pragma once
// FreeType
#include <ft2build.h>
#include FT_FREETYPE_H
// Std. 
#include <map>

// Dream
#include "../Interfaces/IRenderable2d.h"

namespace dream {
	namespace graphics {
				
		class Label : public IRenderable2D
		{
		private:
			std::string					m_Font;				// Default font is arial.
			std::string					m_Text;						
			GLfloat						m_Scale;	
				
		public:			
			Label(const std::string text, maths::Vector2 position, GLfloat scale, unsigned int color);			
			~Label() {};

			inline void SetFont(const std::string& fontFilename) { m_Font = fontFilename; }			

			void Submit(IRenderer2D* renderer) const override;					
		};
	}
}