#include "textureManager.h"

dream::graphics::Texture * dream::graphics::TextureManager::Get(const std::string & name)
{
	for (Texture* texture : m_objects)
		if (texture->GetName() == name)
			return texture;

	return nullptr;
}
