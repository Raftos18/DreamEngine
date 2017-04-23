#include "soundManager.h"

namespace dream {
	namespace audio {

		gau_Manager* SoundManager::m_Manager = nullptr;
		ga_Mixer* SoundManager::m_Mixer = nullptr;		

		void SoundManager::Init()
		{
			// Initialise GorillaAudio
			gc_initialize(0);
			// Create a new manager and store its id
			m_Manager = gau_manager_create();
			// Create a new mixer and store its id
			m_Mixer = gau_manager_mixer(m_Manager);
		}

		void SoundManager::Update()
		{
			// If a manager exists update it 
			if(m_Manager)
				gau_manager_update(m_Manager);
		}
		 
		Sound * SoundManager::Get(const std::string & name)
		{
			for (Sound* sound : m_objects)
			{
				if (sound->GetName() == name)
					return sound;
			}
			return nullptr;
		}	
	}
}


