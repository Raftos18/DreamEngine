#pragma once
// Include Gorilla Audio
#include <gorilla\ga.h>
#include <gorilla\gau.h>
// Include Std.
#include <string>

namespace dream {
	namespace audio {

		class Sound 
		{
		private: 
			std::string m_Name;			// Name of the file(Used in SoundManager).
			std::string m_Filename;		// Path of the file.

			ga_Sound* m_Sound;			
			ga_Handle* m_Handle;
	
			bool m_Playing;				// Indicates whether this sound is currently being played.
			float m_Volume;				// Indicates the volume of the current sound.
			gc_int32 m_Position;
		public:
			Sound(const std::string& name, const std::string& filename);
			~Sound();

			// Call once to start playing the sound.
			void Play();
			// Call once to make the sound loop.
			void Loop();
			// Call once to make the sound stop looping.
			void StopLoop();
			// Call once to pause the sound.
			void Pause();
			// Call once to resume the paused sound.
			void Resume();
			// Call once to stop a sound.
			void Stop();
			// Pass the desired volume for the song.(Min=0.0f, Max=1.0f)
			void SetVolume(float volume);

			// Returns the sound volume.
			inline const float GetVolume() const { return m_Volume; }
			// Returns the name of the sound.
			inline const std::string& GetName() const { return m_Name; }
			// Returns the sound filepath
			inline const std::string& GetFileName() const { return m_Filename; }
			// Return wether the volume of the sound.
			inline const bool isPlaying() const { return m_Playing; }

		private:
			// Callback for when the sound finishes
			friend void SetFlagAndDestroyOnFinish(ga_Handle* in_handle, void* in_context);
		};

	}
}
