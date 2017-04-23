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
			std::string m_Name;						// Name of the texture
			std::string m_Filename;					// Holds the filepath
			GLuint m_TextureId;						// Holds the texture id
			GLsizei m_Width, m_Height;				// Holds the width/ height of the texture

		public:
			Texture(const std::string& name, const std::string& m_filename);
			~Texture();			

			void Bind() const;
			void Unbind() const;

			inline const std::string& GetName() const { return m_Name; }
			inline const std::string& GetFileName() const { return m_Filename; }
			inline const unsigned int GetWidth() const { return m_Width; }
			inline const unsigned int GetHeight() const { return m_Height; }
			inline const GLuint GetTextID() const { return m_TextureId; }

		private:
			GLuint Load();
		};
	}
}

