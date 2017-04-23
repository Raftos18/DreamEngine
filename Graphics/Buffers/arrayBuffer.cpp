// Include Dream
#include "arrayBuffer.h"

namespace dream 
{
	namespace graphics
	{
		ArrayBuffer::ArrayBuffer(GLfloat * data, GLsizei size, GLint componentCount)
			: m_Count(componentCount)
		{
			// Instruct OpenGL to generate a new buffer object and store its id to m_VBO
			glGenBuffers(1, &m_VBO);
			// Bind this buffer object to an GL_ARRAY_BUFFER using the stored id
			glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
			// Pass our user defined data to the bound buffer
			glBufferData(GL_ARRAY_BUFFER, size * sizeof(GLfloat), data, GL_STATIC_DRAW);
			// Release the buffer
			glBindBuffer(GL_ARRAY_BUFFER, 0);
		}

		ArrayBuffer::~ArrayBuffer()
		{
			// Delete the generated buffer
			glDeleteBuffers(1, &m_VBO);
		}

		void ArrayBuffer::Bind() const
		{
			// Bind this buffer object to an GL_ARRAY_BUFFER using the stored id
			glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
		}

		void ArrayBuffer::Unbind() const
		{
			// Bind this buffer object to an GL_ARRAY_BUFFER using the stored id
			glBindBuffer(GL_ARRAY_BUFFER, 0);
		}
	}
}

