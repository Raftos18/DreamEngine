#include "input.h"

namespace dream {
	namespace input {
		// Used to pass the input pointer in the GLFW events.
		Input* ptr_Input;

		Input::Input(GLFWwindow * window)
			: m_Window(window), m_MouseX(0.0f), m_MouseY(0.0f)
		{
			if (Init())
				std::cout << "[Input] Initialised successfully!" << std::endl;
			else
				std::cout << "[Input] failed to initialise!" << std::endl;

			ptr_Input = this;
		}

		bool Input::Init()
		{
			// This must be the first time i use a try/catch in C++. Why not???
			bool success;
			try
			{
				InitMouse();
				InitKeyboard();

				// Set up GLFW callbacks
				glfwSetCursorPosCallback(m_Window, MouseMoveCallback);

				success = true;
			}
			catch (const std::exception&)
			{
				success = false;
			}
			return success;
		}

		bool Input::IsKeyUp(KeyboardKeys keycode)
		{

			// Check that the key code is not biffer that the max GLFW key code
			if ((unsigned int)keycode >= MAX_KEYS)
				return false;
			
			bool success = false;
			// Get the state of the pressed key
			State newState = (State)glfwGetKey(m_Window, (int)keycode);
			// If the keys state is released and its previous state was pressed YOLO
			if (newState == State::RELEASED && m_Keys[(int)keycode] == State::PRESSED)
				success = true;
			else
				success = false;

			// Save its state to the map
			m_Keys[(int)keycode] = newState;

			return success;
		}

		bool Input::IsKeyDown(KeyboardKeys keycode)
		{
			// Check that the key code is not bigger that the max GLFW key code
			if ((unsigned int)keycode >= MAX_KEYS)
				return false;

			bool success = false;

			// Get the state of the pressed key
			State newState = (State)glfwGetKey(m_Window, (int)keycode);
			// If the keys state is pressed and its previous state was released YOLO2
			if (newState == State::PRESSED && m_Keys[(int)keycode] == State::RELEASED)
				success = true;
			else
				success = false;

			// Save its state to the map
			m_Keys[(int)keycode] = newState;

			return success;
		}

		bool Input::IsMouseButtonDown(MouseButtons button)
		{
			// Check that the moyse button code is not bigger that the max GLFW mouse button code
			if ((unsigned int)button >= MAX_MOUSE_BUTTONS)
				return false;

			bool success = false;

			// Get the state of the indicated mouse button
			State newState = (State)glfwGetMouseButton(m_Window, (int)button);
			// If the button state is released and its previous state was pressed 
			if (newState == State::PRESSED && m_MouseButtons[(int)button] == State::RELEASED)
				success = true;
			else
				success = false;

			// Save new state
			m_MouseButtons[(int)button] = newState;

			return success;
		}

		bool Input::IsMouseButtonUp(MouseButtons button)
		{
			// Check that the moyse button code is not bigger that the max GLFW mouse button code
			if ((int)button > MAX_MOUSE_BUTTONS)
				return false;

			bool success = false;

			// Get the state of the indicated mouse button
			State newState = (State)glfwGetMouseButton(m_Window, (int)button);
			// If the keys state is pressed and its previous state was released YOLO2
			if (newState == State::RELEASED && m_MouseButtons[(int)button] == State::PRESSED)
				success = true;
			else
				success = false;

			// Save new button state
			m_MouseButtons[(int)button] = newState;

			return success;
		}

		void Input::GetMousePosition(float& x, float& y)
		{
			x = m_MouseX;
			y = m_MouseY;
		}

		void Input::InitMouse()
		{
			// Set up the mouse buttons map 
			for (int i = 0; i < MAX_MOUSE_BUTTONS; i++)
				m_MouseButtons.insert(std::pair<int, State>(i, State::RELEASED));
		}

		void Input::InitKeyboard()
		{
			// Set up the keyboard map
			for (int i = 0; i < MAX_KEYS; i++)
				m_Keys.insert(std::pair<int, State>(i, State::RELEASED));
		}

		void MouseMoveCallback(GLFWwindow * window, double xpos, double ypos)
		{
			if (ptr_Input)
			{
				ptr_Input->m_MouseX = xpos;
				ptr_Input->m_MouseY = ypos;
			}
		}
	}
}
