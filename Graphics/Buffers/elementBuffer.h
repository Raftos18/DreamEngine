#pragma once

#include <GL\glew.h>

namespace dream
{
	namespace graphics
	{
		class ElementBuffer
		{
		private:
			GLuint m_EBO;				// Holds the id of an OpenGL buffer(GL_VERTEX_ARRAY)
			GLuint m_Count;				// Holds the count of indicies

		public:
			// Generates, binds and stores the data to an element buffer object
			ElementBuffer(GLushort* data, GLsizei count);
			// Generates, binds and stores the data to an element buffer object
			ElementBuffer(GLuint* data, GLsizei count);
			~ElementBuffer();

			// Binds to a Gl_ELEMENT_ARRAY_BUFFER
			void Bind() const;
			// Unbinds the buffer
			void Unbind() const;

			// Returns the count of indicies
			inline GLuint GetCount() const { return m_Count; }
		};
	}
}