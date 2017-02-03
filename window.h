#pragma once
#include <iostream>
#include <GL/glew.h>
#include <glfw3.h>

#define MAX_KEYS 1024
#define MAX_BUTTONS 32

namespace dream
{
	namespace graphics
	{
		class Window
		{
		private:
			const char* m_Title;
			int m_Width, m_Height;
			GLFWwindow* m_Window;
			bool m_IsClosed;

			// I would not put input in the window class
			// nor make it static because of the chance that
			// there will be multiplayer.
			// My solution with the mouse struct is optiomal.
			// The solution from GameCodingComplete is the best.
			bool m_Keys[MAX_KEYS];
			bool m_MouseButtons[MAX_BUTTONS];
			float mx, my;

			bool Init();

		public:
			Window(const char* m_title, int m_width, int height);
			~Window();
			void Clear() const;
			void Update();
			bool Closed() const;

			inline int GetWidth() const { return m_Width;}
			inline int GetHeight() const { return m_Height;}

			bool isKeyPressed(unsigned int keycode) const;
			bool isMouseButtonPressed(unsigned int button) const;
			void GetMousePosition(float& x, float& y) const;

			// This is bad design right here
			// The input shouldn't be here at all
			void friend KeyCallback(GLFWwindow * window, int key, int scancode, int action, int mods);
			void friend MouseButtonCallback(GLFWwindow * window, int key, int button, int action);
			void friend MouseMoveCallback(GLFWwindow * window, double xpos, double ypos);
		};
	}
}
