#include "window.h"


namespace dream
{
	namespace graphics
	{		
		Window::Window(const char* title, int width, int height)
		{
			m_Title = title;
			m_Width = width;
			m_Height = height;

			if (!Init())
				glfwTerminate();

			// Don't like this either.
			for (int i = 0; i < MAX_KEYS; i++)
			{
				m_Keys[i] = false;
			}
			// Don't like this either.
			for (int i = 0; i < MAX_BUTTONS; i++)
			{
				m_MouseButtons[i] = false;
			}

		}

		bool Window::Init()
		{
			if (!glfwInit())
			{
				std::cout << "Failed to initialize GLFW!" << std::endl;
				return false;
			}

			m_Window = glfwCreateWindow(m_Width, m_Height, m_Title, NULL, NULL);
			if (!m_Window)
			{
				std::cout << "Failed to createGLFW window!" << std::endl;

				return false;
			}

			glfwMakeContextCurrent(m_Window);

			glfwSetFramebufferSizeCallback(m_Window, WindowResize);			
			glfwSetWindowUserPointer(m_Window, this);
			glfwSetKeyCallback(m_Window, KeyCallback);
			glfwSetMouseButtonCallback(m_Window, MouseButtonCallback);
			glfwSetCursorPosCallback(m_Window, MouseMoveCallback);

			// Swap to 1.0 to lock frame rate to 60.
			glfwSwapInterval(0.0);

			// Always initialise glew after the context switch.
			if (glewInit() != GLEW_OK)
			{
				std::cout << "Could not initialise GLEW!" << std::endl;

				return false;
			}

			return true;
		}

		Window::~Window()
		{
			glfwTerminate();
		}

		void Window::Clear() const 
		{
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		}

		void Window::Update() 
		{
			GLenum error = glGetError();
			if (error != GL_NO_ERROR)
				std::cout << "OpenGL Error: " << error << std::endl;

			glfwPollEvents();			
			glfwSwapBuffers(m_Window);
		}

		bool Window::Closed() const
		{
			return glfwWindowShouldClose(m_Window) == 1;
		}

		// This should be abstracted better
		bool Window::isKeyPressed(unsigned int keycode) const
		{
			if (keycode >= MAX_KEYS)
				return false;
			else
				return m_Keys[keycode];
		}

		// This should be abstracted better
		bool Window::isMouseButtonPressed(unsigned int button) const
		{
			if (button >= MAX_BUTTONS)
				return false;
			else
				return m_MouseButtons[button];

			return button;
		}

		void Window::GetMousePosition(float & x, float & y) const
		{
			x = mx;
			y = my;
		}

		void WindowResize(GLFWwindow* window, int width, int height)
		{
			glViewport(0, 0, width, height);
			Window* win = (Window*)glfwGetWindowUserPointer(window);
			win->m_Width = width;
			win->m_Height = height;
		}

		void KeyCallback(GLFWwindow * window, int key, int scancode, int action, int mods)
		{
			Window* win = (Window*)glfwGetWindowUserPointer(window);

			// I don't really like this either.
			win->m_Keys[key] = action != GLFW_RELEASE;
		}

		void MouseButtonCallback(GLFWwindow * window, int button, int action, int mods)
		{
			Window* win = (Window*)glfwGetWindowUserPointer(window);

			// Although this works it takes into account only the left click
			win->m_MouseButtons[button] = action != GLFW_MOUSE_BUTTON_LEFT;
		}

		void MouseMoveCallback(GLFWwindow * window, double xpos, double ypos)
		{
			Window* win = (Window*)glfwGetWindowUserPointer(window);

			win->mx = xpos;
			win->my = ypos;
		}
	}
}
