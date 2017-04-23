#include "elementBuffer.h"

namespace dream
{
	namespace graphics
	{		
		ElementBuffer::ElementBuffer(GLushort * data, GLsizei count)
			: m_Count(count)
		{
			// Instruct OpenGL to generate a new buffer object and store its id to m_EBO
			glGenBuffers(1, &m_EBO);
			// Bind the generated buffer to a GL_ELEMENT_ARRAY_BUFFER
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);
			// Pass our user defined data
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(GLushort), data, GL_STATIC_DRAW);
			// Unbind buffer for later use
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
		}

		ElementBuffer::ElementBuffer(GLuint * data, GLsizei count)
			: m_Count(count)
		{
			// Instruct OpenGL to generate a new buffer object and store its id to m_EBO
			glGenBuffers(1, &m_EBO);
			// Bind the generated buffer to a GL_ELEMENT_ARRAY_BUFFER
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);
			// Pass our user defined data (Indicies)
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(GLuint), data, GL_STATIC_DRAW);
			// Unbind buffer for later use
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
		}

		ElementBuffer::~ElementBuffer()
		{
			// Delete the generated buffer
			glDeleteBuffers(1, &m_EBO);
		}

		void ElementBuffer::Bind() const
		{
			// Bind the generated buffer to a GL_ELEMENT_ARRAY_BUFFER
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);
		}

		void ElementBuffer::Unbind() const
		{
			// Unbind buffer for later use
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
		}
	}
}

