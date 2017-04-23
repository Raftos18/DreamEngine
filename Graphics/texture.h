#pragma once

// Include FreeImage
#include <FreeImage.h>
// Include OpenGL
#include <GL\glew.h>
// Include Std
#include <string>

namespace dream
{
	namespace graphics
	{
		class Texture
		{
		private:
			std::string m_name;
			std::string m_filename;
			GLuint m_tID;
			GLsizei m_width, m_height;

		public:
			Texture(const std::string& name, const std::string& m_filename);
			~Texture();
			void Bind() const;
			void Unbind() const;

			inline const std::string& GetName() const { return m_name; }
			inline const std::string& GetFileName() const { return m_filename; }
			inline const unsigned int GetWidth() const { return m_width; }
			inline const unsigned int GetHeight() const { return m_height; }
			inline const GLuint GetTextID() const { return m_tID; }

		private:
			GLuint Load();
		};
	}
}

