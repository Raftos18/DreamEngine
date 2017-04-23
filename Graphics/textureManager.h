#pragma once

#include "../Interfaces/IManager.h"
#include "./texture.h"

namespace dream {
	namespace graphics {

		class TextureManager : public IManager<Texture>
		{
			friend class Texture;
		private:
			TextureManager() {};
		public:
			static TextureManager& Instance() 
			{
				static TextureManager instance;
				return instance;
			}			

			void Init() override { /*No Initialization needed*/};			
			Texture* Get(const std::string& name);			
		};
	}
}