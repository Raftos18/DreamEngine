#pragma once

// Include Dream
#include "sound.h"
#include "../Interfaces/IManager.h"

namespace dream {
	namespace audio {

		// SoundManager is a singleton used to play 
		// and organise sounds
		class SoundManager : public IManager<Sound>
		{
			friend class Sound;	
		private:
			static gau_Manager* m_Manager;		
			static ga_Mixer* m_Mixer;

		private:
			SoundManager() {};
		public:
			// Lazy initialazation, create a new static instance
			// the first time it is requested
			static SoundManager& Instance()
			{
				static SoundManager instance;
				return instance;
			}
			// Initialises the SoundManager
			void Init() override;
			// Call it once every frame
			void Update();
			// Returns a sound indicated by the name
			Sound* Get(const std::string& name);
		};
	}
}