// Include Std
#include <iostream>
// Include Dream
#include "sound.h"
#include "soundManager.h"
#include "../Utils/dreamUtils.h"

namespace dream {
	namespace audio {				

		Sound::Sound(const std::string & name, const std::string & filename):
			m_Name(name), m_Filename(filename), m_Playing(false)
		{
			// split filename on '.' to get the file format.
			std::vector<std::string> elements = utilities::String::Split(m_Filename, '.');

			// if the elements of the filename are less than 2 we can't get the format of the file.
			if (elements.size() < 2)
				std::cout << "[Sound] Invalid file name " << m_Filename << "!\n";

			// load file onto the gorilla audio
			m_Sound = gau_load_sound_file(filename.c_str(), elements.back().c_str());

			// gorilla couldn't load file.
			if (m_Sound == nullptr)
				std::cout << "[Sound] Could not load file " << m_Filename << ". Check for supported formats" << "!\n";
		}

		Sound::~Sound()
		{
			// Clean resources by releasing the handle.
			ga_sound_release(m_Sound);
		}

		void Sound::Play()
		{
			gau_SampleSourceLoop* loopSrc = 0; 
			gau_SampleSourceLoop** pLoopSrc = &loopSrc;

			gc_int32 loop = 1; 
			gc_int32 quit = 0;

			// I don't really remember why i did this. Propably should remove.
			if (loop)
				pLoopSrc = 0;				

			// create a new handle in order to call play.
			m_Handle = gau_create_handle_sound(SoundManager::m_Mixer, m_Sound, &SetFlagAndDestroyOnFinish, &quit, nullptr);

			// call play on the returned handle.
			ga_handle_play(m_Handle);

			// set is playing to true for this sound.
			m_Playing = true;
		}

		void Sound::Loop()
		{						
			// Check gorilla doc(Simple)
			gau_SampleSourceLoop* loopSrc = 0;			
			gau_sample_source_loop_set(loopSrc, -1, 0);
		}

		void Sound::StopLoop()
		{
			// Check gorilla doc(Simple)
			gau_SampleSourceLoop* loopSrc = 0;
			gau_sample_source_loop_clear(loopSrc);
		}

		void Sound::Resume()
		{
			// If already playing return.
			if (m_Playing)
				return;

			// Call play.
			Play();
			// Call set volume because volume resets after pause.
			SetVolume(m_Volume);
			// Move to the position saved a the last pause.
			ga_handle_seek(m_Handle, m_Position);
		}

		void Sound::Pause()
		{
			// If sound doen't play already return
			if (!m_Playing)
				return;

			// set playing to false
			m_Playing = false;
			// call stop to this sound handle
			ga_handle_stop(m_Handle);
			// save the last played position in the sound.(Used in Resume)
			m_Position = ga_handle_tell(m_Handle, GA_TELL_PARAM_CURRENT);
		}

		void Sound::Stop()
		{
			// If sound doen't play already return
			if (!m_Playing)
				return;

			// use sound handle to call stop
			ga_handle_stop(m_Handle);
			// set playing to false
			m_Playing = false;
		}

		void Sound::SetVolume(float volume)
		{
			if (!m_Playing)
			{
				std::cout << "Sound must be playing to set volume" << std::endl;
				return;
			}
			// In case the volume somehow went over the 1.0f upper threshold return it there.
			if (volume > 1.0f)
				volume = 1.0f;			
			// In case the volume somehow went under the 0.0f lower threshold return it there.
			if (volume < 0.0f) 
				volume = 0.0f;						
			
			// set current volume.
			m_Volume = volume;
			// update sound to current volume.
			ga_handle_setParamf(m_Handle, GA_HANDLE_PARAM_GAIN, m_Volume);
		}

		void SetFlagAndDestroyOnFinish(ga_Handle* in_handle, void* in_context)
		{		
			ga_handle_destroy(in_handle);						
		}
	}
}



