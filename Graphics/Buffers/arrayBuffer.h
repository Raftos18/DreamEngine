#pragma once

// Include GLEW
#include <GL\glew.h>

namespace dream 
{
	namespace graphics
	{
		// ArrayBuffer is implemented using RAII. 
		// If used with smart pointers it will guarantee that no memory leaks occur.
		class ArrayBuffer 
		{
		private:
			GLuint m_VBO;			// Holds the id of an OpenGL buffer(GL_ARRAY_BUFFER)
			GLuint m_Count;			// Holds the count of the components			

		public:
			// Default constructor. Generate, bind and stores data to the ArrayBuffer object
			ArrayBuffer(GLfloat* data, GLsizei size, GLint componentCount);
			~ArrayBuffer();
			
			// Binds a generated ArrayBuffer to a GL_ARRAY_BUFFER
			void Bind() const;
			// Nuff said (¬_¬)
			void Unbind() const;

			// Returns the component count pass to the ArrayBuffer.
			inline GLuint GetComponentCount() const { return m_Count; }
		};
	}
}