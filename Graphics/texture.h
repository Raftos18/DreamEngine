#pragma once

#include <FreeImage.h>
#include <GL\glew.h>
#include <string>

#include "Utils\ImageLoad.h"

namespace dream
{
	namespace graphics
	{
		class Texture
		{
		private:
			std::string m_filename;
			GLuint m_tID;
			GLsizei m_width, m_height;

		public:
			Texture(const std::string& m_filename);
			~Texture();
			void Bind() const;
			void Unbind() const;

			inline const unsigned int GetWidth() const { return m_width; }
			inline const unsigned int GetHeight() const { return m_height; }
			inline const GLuint GetTextID() const { return m_tID; }

		private:
			GLuint Load();
		};
	}
}

