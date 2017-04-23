#pragma once
//  Windows

// Include Std
#include <string>
#include <iostream>
#include <sstream>
#include <vector>
#include <cstdint>

// Include OpenGL
#include <GL\glew.h>

// Include 
#include <FreeImage.h>

// Notes create cpp files for all utilities.

namespace dream {
	namespace utilities {
		
		class Timer
		{
		private:
			uint64_t m_timerStart;
			uint64_t m_timerElapsed;			

			float    m_resolution;									
			float	 m_diffTime;
			float	 m_fps;
			bool	 m_isPaused;			
			
			float	 m_time1;
			float	 m_time2;
			int		 m_framesElapsed;

			static float m_cyclesPerSecond;

		public:
			static inline uint64_t SecondsToCycles(float seconds);
			// According to Game Engine Architecture. This should only be used for small durations.
			static inline float CyclesToSeconds(long timeCycles);		

			// Call Init at the start of the game.
			bool Init();
			
			// Sets the TimeCycles to the current from the start of the program
			Timer();						

			explicit Timer(float startTimeSeconds);

			virtual ~Timer() {};

			// Return the current time in cycles. NOTE that we do
			// not return absolute time measurements in floating-
			// point seconds, because a 32-bit float doesn't have
			// enough precision.
			uint64_t GetTimeCycles() const;						

			// Time cycles in seconds.
			float GetElapsedSeconds() const;

			// Gets the time since the program started.
			float GetTime();

			// 
			void Update();								
			// Resets the time to 0.0f.
			void Reset();

			// Calculates the delta betweew two Timer objects.
			float CalcDeltaSeconds(const Timer& other);
			
			void SetPaused(bool paused);
			bool GetPaused() const;		

			// Returns the frames per second
			float GetFPS();
		};

		class String
		{
		public:
			// Splits a given string about a specified delimeter and returns a vector with all the splited elements
			static std::vector<std::string> Split(const std::string &s, char delim);
		};

		class File
		{
		public:
			// Reads a file and returns a string with its contents.
			static std::string ReadFile(const char* filepath);
			// returns a specified images as a byte array.
			static BYTE* LoadImage(const char* filename, GLsizei* width, GLsizei* height);
		};
	}
}