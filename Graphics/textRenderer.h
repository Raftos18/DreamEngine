#pragma once
// Std.
#include <map>
//
// GL
#include <GL\glew.h>
// FreeType
#include <ft2build.h>
#include FT_FREETYPE_H
//
// Dream
#include "../Interfaces/IRenderer2d.h"

namespace dream {
	namespace graphics {

		struct Character {					
			GLuint TextureID;   // ID handle of the glyph texture
			maths::Vector2 Size;    // Size of glyph
			maths::Vector2 Bearing;  // Offset from baseline to left/top of glyph
			GLuint Advance;    // Horizontal offset to advance to next glyph
		};

		// Currently broken.
		// Need to be intergrated into the rest of the program.
		class TextRenderer : public IRenderer2D
		{
		private:			
			GLuint m_VAO;
			GLuint m_VBO;

			FT_Library					m_Lib;
			FT_Face						m_Face;			
			std::map<GLchar, Character> m_Characters;
	
		public:
			TextRenderer();
			~TextRenderer();

			void RenderText(const std::string& font, const std::string& text, float x, float y, float scale, unsigned int color) override;
			
		protected:
			void Init();
			void Flush() override;

			void GenerateCharacters();
			void CleanFreeType();
		};

	}
}


