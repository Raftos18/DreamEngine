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
			ElementBuffer(GLuint* data, GLsizei count);
			~ElementBuffer();

			// Binds to a Gl_ELEMENT_ARRAY_BUFFER
			void Bind() const;
			// Unbinds the buffer
			void Unbind() const;

			// Creates a Indexed Triangle list stored in an array and returns a pointer to it
			// Call delete when no longer needed. Smart Pointers whould be a really good idea here
			static GLuint* CreateIndexTriangles(int indicesSize);

			// Returns the count of indicies
			inline GLuint GetCount() const { return m_Count; }
		};
	}
}