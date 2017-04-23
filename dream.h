#pragma once
// Include Dream(Graphics)
#include "./System/window.h"
#include "./Input/input.h"
#include "./Graphics/Layers/layers.h"
#include "./Graphics/Shaders/shader.h"
#include "./Graphics/textureManager.h"
#include "./Graphics/sprite.h"
#include "./Graphics/renderer2d.h"
// Include Dream(Audio)
#include "Audio/soundManager.h"
// Include Dream(Utilities)
#include "./Utils/dreamUtils.h" 

namespace dream {
	class Dream 
	{
	private:
		system::Window*					m_Window;
		input::Input*				    m_Input;
		utilities::Timer*			    m_Timer;				

		int						        m_FramesPerSeconds;		
	protected:	
		Dream() : m_FramesPerSeconds(0)
		{
			m_Timer->Init();

			// Init Managers
			graphics::TextureManager::Instance().Init();
			audio::SoundManager::Instance().Init();
		};

		virtual ~Dream() 
		{	
			// Clean Managers
			graphics::TextureManager::Instance().Clean();
			audio::SoundManager::Instance().Clean();

			delete m_Timer;
			delete m_Window;
		};

		// Creates a new window and returns it.
		system::Window* CreateDreamWindow(const char *name, int width, int height)
		{
			m_Window = new system::Window(name, width, height);			
			m_Input = new input::Input(m_Window->GetWindowHandle());			

			return m_Window;
		}

		// Call to start the Game Loop
		void Start()
		{
			Init();
			Run();
		}

		// Runs upon initialization
		virtual void Init() = 0;
		// Runs once per second
		virtual void Tick() = 0;		
		// Runs every frame to update the game state
		virtual void Update() = 0;
		// Runs every frame to draw the game state
		virtual void Render() = 0;

		// Returns the FPS(Frame Per Second) the engine is currently running.
		const unsigned int GetFPS() { return m_FramesPerSeconds; }		

	private:
		// Begins the Game Loop
		void Run()
		{
			m_Timer = new utilities::Timer();			

			float timer = 0.0f;			
			// Game Loop
			while (!m_Window->Closed())
			{
				m_Window->Clear();				
				
				if (timer < 1.0f)
				{
					// Updates 
					Update();
					// Render 
					Render();
					//Update Audio 
					audio::SoundManager::Instance().Update();
					// Update Window
					m_Window->Update();
					// Update timer
					m_Timer->Update();
				}
				else 
				{
					// Updates once a second.
					Tick();
					timer = 0.0f;
				}				
			}		
		}
	};
}
