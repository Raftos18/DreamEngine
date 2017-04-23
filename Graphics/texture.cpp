// Include Dream
#include "texture.h"
#include "../Utils/dreamUtils.h"


dream::graphics::Texture::Texture(const std::string& name, const std::string & filename)
	: m_Name(name), m_Filename(filename)
{
	// Save the textrure id assigned from OpenGL
	m_TextureId = Load();
}

dream::graphics::Texture::~Texture()
{
	
}

void dream::graphics::Texture::Bind() const
{
	// Bind a openGL texture to the texture id
	glBindTexture(GL_TEXTURE_2D, m_TextureId);
}

void dream::graphics::Texture::Unbind() const
{
	// Unbind OpenGL texture
	glBindTexture(GL_TEXTURE_2D, 0);
}

GLuint dream::graphics::Texture::Load()
{
	// Load image from file
	BYTE* pixels = utilities::File::LoadImage(m_Filename.c_str(), &m_Width, &m_Height);	
	GLuint textureID;

	// Generate a new texture and save the id returned from OpenGL
	glGenTextures(1, &textureID);
	// Bind a OpenGL texture to the id 
	glBindTexture(GL_TEXTURE_2D, textureID);
	// Set up the texture parameters 
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	// Pass texture object data to OpenGL
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, m_Width, m_Height, 0, GL_BGR, GL_UNSIGNED_BYTE, pixels);
	// Unbind for later use
	glBindTexture(GL_TEXTURE_2D, 0);

	delete[] pixels;

	return textureID;
}
