#include "textureManager.h"
#include "renderer2d.h"

namespace dream {
	namespace graphics {

		TextureManager::TextureManager()
		{
			m_TextIds = new GLint[RENDERER_MAX_TEXTURES]{
				0,	1,	2,	3,	4,	5,	6,	7,	8,	9,
				10,	11,	12,	13,	14,	15,	16,	17,	18,	19,
				20,	21,	22,	23,	24,	25,	26,	27,	28,	29,
				30, 31
			};
		}

		TextureManager::~TextureManager()
		{
			GLuint* textId = new GLuint[m_objects.size()];
			for (size_t i = 0; i < m_objects.size(); i++)
				textId[i] = m_objects[i]->GetTextID();
			glDeleteTextures(m_objects.size(), textId);

			delete m_TextIds;

			IManager::~IManager();
		}

		void TextureManager::BindTextureArray(std::vector<GLuint>* textures)
		{
			for (size_t i = 0; i < textures->size(); i++)
			{
				glActiveTexture(GL_TEXTURE0 + i);
				glBindTexture(GL_TEXTURE_2D, (*textures)[i]);
			}
		}

		Texture * dream::graphics::TextureManager::Get(const std::string & name)
		{
			for (Texture* texture : m_objects)
				if (texture->GetName() == name)
					return texture;

			return nullptr;
		}
	}
}

