#pragma once

#include "../Interfaces/IManager.h"
#include "./texture.h"

namespace dream {
	namespace graphics {

		class TextureManager : public IManager<Texture>
		{
			friend class Texture;
		private:
			GLint* m_TextIds;

		private:
			TextureManager();
			~TextureManager() override;		

		public:
			static TextureManager& Instance() 
			{
				static TextureManager instance;
				return instance;
			}			

			static void BindTextureArray(std::vector<GLuint>* textures);

			void Init() override { /*No Initialization needed*/};					
			Texture* Get(const std::string& name);			
			GLint* GetTextureIds(){ return m_TextIds; }
		};
	}
}