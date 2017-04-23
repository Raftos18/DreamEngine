// Include Dream
#include "texture.h"
#include "../Utils/dreamUtils.h"


dream::graphics::Texture::Texture(const std::string& name, const std::string & filename)
	: m_name(name), m_filename(filename)
{
	m_tID = Load();
}

dream::graphics::Texture::~Texture()
{

}

void dream::graphics::Texture::Bind() const
{
	glBindTexture(GL_TEXTURE_2D, m_tID);
}

void dream::graphics::Texture::Unbind() const
{
	glBindTexture(GL_TEXTURE_2D, 0);
}

GLuint dream::graphics::Texture::Load()
{
	BYTE* pixels = utilities::File::LoadImage(m_filename.c_str(), &m_width, &m_height);	
	GLuint result;

	glGenTextures(1, &result);
	glBindTexture(GL_TEXTURE_2D, result);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, m_width, m_height, 0, GL_BGR, GL_UNSIGNED_BYTE, pixels);
	glBindTexture(GL_TEXTURE_2D, 0);

	delete[] pixels;

	return result;
}
