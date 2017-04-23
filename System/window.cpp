// Include Std
#include <iostream>
// Include Dream
#include "window.h"

namespace dream
{
	namespace system
	{		
		Window::Window(const char* title, int width, int height, bool fullscreen)						
		{
			m_Title = title;
			m_Width = width;
			m_Height = height;
			m_IsVSyncOn = true;

			if (!Init(fullscreen))
				glfwTerminate();

			glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
			glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
			glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
			glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

			m_Monitor = glfwGetPrimaryMonitor();			
		}

		bool Window::Init(bool fullscreen)
		{
			if (!glfwInit())
			{
				std::cout << "[Window] Failed to initialize GLFW!\n";
				return false;
			}
			
			// Create window either on fullscreen or windowed mode
			if(fullscreen)
				m_Window = glfwCreateWindow(m_Width, m_Height, m_Title, glfwGetPrimaryMonitor(), NULL);
			else
				m_Window = glfwCreateWindow(m_Width, m_Height, m_Title, NULL, NULL);

			// If window failed to be created notify user
			if (!m_Window)
			{
				std::cout << "[Window] Failed to createGLFW window!\n";
				return false;
			}
			// Make context switch
			glfwMakeContextCurrent(m_Window);

			// Set window callbacks
			glfwSetFramebufferSizeCallback(m_Window, GLFWResiseWindow);
			glfwSetWindowUserPointer(m_Window, this);	

			// Set VSync			
			glfwSwapInterval(m_IsVSyncOn);

			// Important to initialise glew after context switch
			if (glewInit() != GLEW_OK)
			{
				std::cout << "[Window] Could not initialise GLEW!\n";
				return false;
			}			

			return true;
		}

		Window::~Window()
		{					
			// Terminate glfw operations
			glfwTerminate();
			// Destroy all windows
			glfwDestroyWindow(m_Window);
		}

		void Window::Clear() const 
		{
			// Clear the current color and depth buffers
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
			glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
		}

		void Window::Update() 
		{
			// Get any error that might occur and inform user
			GLenum error = glGetError();
			if (error != GL_NO_ERROR)
				std::cout << "[Window] OpenGL Error: " << error << std::endl;

			glfwPollEvents();			
			glfwSwapBuffers(m_Window);
		}

		void Window::Close()
		{
			// Indicate to glfw that you want to close the window
			glfwSetWindowShouldClose(m_Window, 1);
		}

		bool Window::Closed() const
		{
			if (glfwWindowShouldClose(m_Window) == 1)
				return true;
			else 
				return false;			
		}

		void Window::MakeFullscreen()
		{			
			// Gety the mode for the current monitor
			const GLFWvidmode* mode = glfwGetVideoMode(m_Monitor);
			// Make window fullscreen
			glfwSetWindowMonitor(m_Window, m_Monitor, 0, 0, mode->width, mode->height, mode->refreshRate);
			SetVSync(m_IsVSyncOn);
		}
	
		void GLFWResiseWindow(GLFWwindow * window, int width, int height)
		{
			glViewport(0, 0, width, height);
			Window* win = (Window*)glfwGetWindowUserPointer(window);
			win->m_Width = width;
			win->m_Height = height;
		}
	}
}
