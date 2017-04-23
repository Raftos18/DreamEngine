#pragma once
// Include Win API
#include <Windows.h>
// Include Dream
#include "dreamUtils.h"

namespace dream {
	namespace utilities {
		
		float Timer::m_cyclesPerSecond;		

		Timer::Timer(float startTimeSeconds)
			: m_timerStart(SecondsToCycles(startTimeSeconds)), m_isPaused(false)
		{
		}

		Timer::Timer()
			: m_isPaused(false), m_timerStart(0), m_timerElapsed(0), 
			m_resolution(0.0f), m_diffTime(0.0f), m_fps(0.0f), m_time1(0.0f), m_time2(0.0f)
		{						
		}

		inline uint64_t Timer::SecondsToCycles(float seconds)
		{
			return (uint64_t)(seconds * m_cyclesPerSecond);
		}

		inline float Timer::CyclesToSeconds(long timeCycles)
		{
			return (float)timeCycles / m_cyclesPerSecond;
		}

		bool Timer::Init()
		{
			LARGE_INTEGER li;
			if (m_cyclesPerSecond <= 0) {
				if (!QueryPerformanceFrequency(&li))
				{
					std::cout << "Failed to QueryPerformanceFrequency" << std::endl;
					return false;
				}
				m_cyclesPerSecond = (float)li.QuadPart;
			}

			//get the current time and store it.
			QueryPerformanceCounter(&li);
			m_timerStart = li.QuadPart;
			
			// calculate the timer resolution. This could be static too i think.
			m_resolution = (float)(((double)1.0f) / ((double)m_cyclesPerSecond));

			// Init elapsed time
			m_timerElapsed = m_timerStart;

			return true;
		}

		uint64_t Timer::GetTimeCycles() const
		{
			return m_timerStart;
		}

		float Timer::GetElapsedSeconds() const
		{			
			return m_diffTime;
		}

		float Timer::GetTime()
		{			
			LARGE_INTEGER il;
			QueryPerformanceCounter(&il);
			uint64_t time = il.QuadPart;

			return ((float)(time - m_timerStart) * m_resolution) * 1000;
		}

		void Timer::Update()
		{
			if (!m_isPaused) 
			{				
				m_framesElapsed++;
				
				// Can't remember why i chose mod 6 but it could be anything
				if (m_framesElapsed % 6 == 1)
					m_time1 = GetTime() / 1000;
				else if (m_framesElapsed % 6 == 0)
				{
					m_time1 = m_time2;
					m_time2 = GetTime() / 1000;
					m_diffTime = (float)fabs(m_time2 - m_time1);
				}
				m_fps = 6 / (m_diffTime);
			}
		}
	
		// Doesn't really work as intended
		void Timer::Reset()
		{
			m_timerStart = 0.0f;
			m_framesElapsed = m_timerStart;
			m_diffTime = 0.0f;
		}

		float Timer::CalcDeltaSeconds(const Timer & other)
		{
			uint64_t dt = m_timerStart - other.m_timerStart;
			return CyclesToSeconds(dt);
		}

		inline void Timer::SetPaused(bool paused)
		{
			m_isPaused = paused;
		}

		inline bool Timer::GetPaused() const
		{
			return m_isPaused;
		}
		float Timer::GetFPS()
		{
			return m_fps;
		}
	}
}