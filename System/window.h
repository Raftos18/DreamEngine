#pragma once
// Include GLEW
#include <GL\glew.h>
// Include GLFW
#include <glfw3.h>

namespace dream
{
	namespace system
	{
		// Typical window class utilizing GLFW and GLEW
		class Window
		{	
		private:
			const char*			m_Title;				// Title of the window as a char array
			int					m_Width;				// Width of the current window
			int					m_Height;				// Height of the current window
			GLFWwindow*			m_Window;				// The GLFWwindow handle pointer
			GLFWmonitor*		m_Monitor;				// The GLFWmonitor handle pointer			
			bool				m_IsVSyncOn;			// Indicates whether VSync is on

		private:
			// Called from constructor for initializing the Window object
			bool Init(bool fullscreen);

		public:
			// Default constructor
			Window(const char* m_title, int m_width, int height, bool fullscreen = false);
			virtual ~Window();

			// Clears the current window screen
			void Clear() const;
			// Call it every frame to update current window(Swap Buffers, PollWindowEvents)
			void Update();
			// Call it to promt a window closing event
			void Close();
			// Idicates whether the window has closed
			bool Closed() const;

			// Returns a pointer to the current window handle
			inline GLFWwindow* GetWindowHandle() const { return m_Window; }			
			// Returns the current width of the window
			inline int GetWidth() const { return m_Width;}
			// Returns the current height of the window
			inline int GetHeight() const { return m_Height;}							

			// Makes the window full screen
			void MakeFullscreen();			

			// Returns whether VSync is on/off
			inline bool GetVSync() const { return m_IsVSyncOn; }
			// Sets VSync to on/off
			inline void SetVSync(bool toggle) 
			{
				m_IsVSyncOn = toggle; 
				glfwSwapInterval(m_IsVSyncOn);
			}			
			// Friend function called as callback
			friend void GLFWResiseWindow(GLFWwindow * window, int width, int height);
		};
	}
}
