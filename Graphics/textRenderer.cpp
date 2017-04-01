#include "textRenderer.h"

namespace dream {
	namespace graphics {

		TextRenderer::TextRenderer(const std::string fontFilename)
		{
			// Suspect for multithreading
			Init(fontFilename);
			GenerateCharacters();

			// Initialize GLEW to setup the OpenGL Function pointers
			glewExperimental = GL_TRUE;
			
			// Set OpenGL options
			glEnable(GL_CULL_FACE);
			glEnable(GL_BLEND);
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);				
		}

		TextRenderer::~TextRenderer()
		{
			CleanFreeType();
		}

		void TextRenderer::Init(const std::string fontFilename)
		{					
			// All functions return a value different than 0 whenever an error occurred
			if (FT_Init_FreeType(&m_Lib))
				std::cout << "ERROR::FREETYPE: Could not init FreeType Library" << std::endl;

			// Load font as face			
			if (FT_New_Face(m_Lib, fontFilename.c_str(), 0, &m_Face))
				std::cout << "ERROR::FREETYPE: Failed to load font" << std::endl;

			// Set size to load glyphs as
			FT_Set_Pixel_Sizes(m_Face, 0, 48);

			// Disable byte-alignment restriction
			glPixelStorei(GL_UNPACK_ALIGNMENT, 1);			

			// Configure VAO/VBO for texture quads
			glGenVertexArrays(1, &VAO);
			glGenBuffers(1, &VBO);

			glBindVertexArray(VAO);
			glBindBuffer(GL_ARRAY_BUFFER, VBO);
			glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 6 * 4, NULL, GL_DYNAMIC_DRAW);

			glEnableVertexAttribArray(0);

			glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), 0);
			glBindBuffer(GL_ARRAY_BUFFER, 0);

			glBindVertexArray(0);
		}

		void TextRenderer::CleanFreeType()
		{
			glBindTexture(GL_TEXTURE_2D, 0);
			// Destroy FreeType once we're finished
			FT_Done_Face(m_Face);
			FT_Done_FreeType(m_Lib);
		}

		void TextRenderer::GenerateCharacters()
		{
			// Load first 128 characters of ASCII set
			for (GLubyte c = 0; c < 128; c++)
			{
				// Load character glyph 
				if (FT_Load_Char(m_Face, c, FT_LOAD_RENDER))
				{
					std::cout << "ERROR::FREETYTPE: Failed to load Glyph" << std::endl;
					continue;
				}
				// Generate texture
				GLuint texture;
				glGenTextures(1, &texture);
				glBindTexture(GL_TEXTURE_2D, texture);
				glTexImage2D(
					GL_TEXTURE_2D,
					0,
					GL_RED,
					m_Face->glyph->bitmap.width,
					m_Face->glyph->bitmap.rows,
					0,
					GL_RED,
					GL_UNSIGNED_BYTE,
					m_Face->glyph->bitmap.buffer
				);
				// Set texture options
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
				// Now store character for later use
				Character character = {
					texture,
					maths::Vector2(m_Face->glyph->bitmap.width, m_Face->glyph->bitmap.rows),
					maths::Vector2(m_Face->glyph->bitmap_left,  m_Face->glyph->bitmap_top),
					m_Face->glyph->advance.x
				};
				m_Characters.insert(std::pair<GLchar, Character>(c, character));
			}			
		}

		void TextRenderer::RenderText(const std::string & text, float x, float y, float scale, maths::Vector3 & color)
		{			
			glActiveTexture(GL_TEXTURE0);
			glBindVertexArray(VAO);

			// Iterate through all characters
			std::string::const_iterator c;
			for (c = text.begin(); c != text.end(); c++)
			{
				Character ch = m_Characters[*c];

				GLfloat xpos = x + ch.Bearing.m_X * scale;
				GLfloat ypos = y - (ch.Size.m_Y - ch.Bearing.m_Y) * scale;

				GLfloat w = ch.Size.m_X * scale;
				GLfloat h = ch.Size.m_Y * scale;
				// Update VBO for each character
				GLfloat vertices[6][4] = {
					{ xpos,     ypos + h,   0.0, 0.0 },
					{ xpos,     ypos,       0.0, 1.0 },
					{ xpos + w, ypos,       1.0, 1.0 },

					{ xpos,     ypos + h,   0.0, 0.0 },
					{ xpos + w, ypos,       1.0, 1.0 },
					{ xpos + w, ypos + h,   1.0, 0.0 }
				};
				// Render glyph texture over quad
				glBindTexture(GL_TEXTURE_2D, ch.TextureID);
				// Update content of VBO memory
				glBindBuffer(GL_ARRAY_BUFFER, VBO);
				glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices); // Be sure to use glBufferSubData and not glBufferData

				glBindBuffer(GL_ARRAY_BUFFER, 0);
				// Render quad
				glDrawArrays(GL_TRIANGLES, 0, 6);
				// Now advance cursors for next glyph (note that advance is number of 1/64 pixels)
				x += (ch.Advance >> 6) * scale; // Bitshift by 6 to get value in pixels (2^6 = 64 (divide amount of 1/64th pixels by 64 to get amount of pixels))
			}

			glBindVertexArray(0);
			glBindTexture(GL_TEXTURE_2D, 0);
		}		
	}
}