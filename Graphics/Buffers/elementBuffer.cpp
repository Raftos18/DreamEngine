#include "elementBuffer.h"

namespace dream
{
	namespace graphics
	{		
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

		GLuint * ElementBuffer::CreateIndexTriangles(int indicesSize)
		{
			// Create the array that will hold the indicies
			GLuint* indices = new GLuint[indicesSize];

			int offset = 0;
			// Each loop create two triangle(Each made of three indices)
			for (unsigned int i = 0; i < indicesSize; i += 6)
			{
				// First triangle 
				indices[  i  ] = offset + 0;
				indices[i + 1] = offset + 1;
				indices[i + 2] = offset + 3;
				// Second triangle 
				indices[i + 3] = offset + 1;
				indices[i + 4] = offset + 2;
				indices[i + 5] = offset + 3;
						
				// add 4 to offset to get to the next first index 
				offset += 4;
			}			

			return indices;
		}		
	}
}

