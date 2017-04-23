#pragma once
// Include GLEW
#include <GL\glew.h>
// Include GLFW
#include <glfw3.h>
// Include Std
#include <iostream>
#include <map>
// Include Dream
#include "InputEnums.h"

#define MAX_KEYS 348				//	Max value of GLFW_KEYS is 348
#define MAX_MOUSE_BUTTONS 3

namespace dream 
{
	namespace input 
	{
		class Input 
		{						
		private:			
			GLFWwindow* m_Window;							// The GLFWwindow handle
			std::map<int, State> m_Keys;					// Holds all the keyboard keys and their state
			std::map<int, State> m_MouseButtons;			// Holds all the mouse buttons and their state
			float m_MouseX, m_MouseY;						// Hold the mouse coordinates

		public:
			Input(GLFWwindow* window);			

			// Return whether a key that was pressed has been released
			bool IsKeyUp(KeyboardKeys keycode);
			// Returns whether a key has been pressed
			bool IsKeyDown(KeyboardKeys keycode);

			// Return whether a mouse button that was pressed has been released
			bool IsMouseButtonDown(MouseButtons button);
			// Returns whether a mouse button has been pressed
			bool IsMouseButtonUp(MouseButtons button);

			// Sets the position of mouse to the two provided variables
			void GetMousePosition(float& x, float& y);

		private:			
			bool Init();
			void InitMouse();
			void InitKeyboard();

			// Called when the mouse moves
			void friend MouseMoveCallback(GLFWwindow * window, double xpos, double ypos);			
		};
	}
}
