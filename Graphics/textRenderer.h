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
#include "renderer2d.h"

namespace dream {
	namespace graphics {

		struct Character {
			GLuint TextureID;   // ID handle of the glyph texture
			maths::Vector2 Size;    // Size of glyph
			maths::Vector2 Bearing;  // Offset from baseline to left/top of glyph
			GLuint Advance;    // Horizontal offset to advance to next glyph
		};

		// MAKE THE TWO RENDERERS WORK TOGETHER.
		// MAKE POSSIBLE TO CHANGE COLORS AND FONTS ON THE FLY.
		class TextRenderer : public IRenderer2D
		{
		private:
			GLuint						VAO;
			GLuint						VBO;

			FT_Library					m_Lib;
			FT_Face						m_Face;
			std::map<GLchar, Character> m_Characters;
	
		public:
			TextRenderer(const std::string fontFilename);
			~TextRenderer();

			void RenderText(const std::string& text, float x, float y, float scale, maths::Vector3& color) override;

		private:
			void Init(const std::string fontFilename);
			void GenerateCharacters();
			void CleanFreeType();
		};

	}
}


