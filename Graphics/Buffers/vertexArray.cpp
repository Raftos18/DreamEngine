#include "vertexArray.h"

namespace dream
{
	namespace graphics
	{
		VertexArray::VertexArray()
		{
			glGenVertexArrays(1, &m_VAO);
		}

		dream::graphics::VertexArray::~VertexArray()
		{
			// Modern approach
			for (std::vector<ArrayBuffer*>::const_iterator iter = m_Buffers.begin(); 
				iter != m_Buffers.end(); iter++)			
				delete *iter;

			// Delete vertex array buffer
			glDeleteVertexArrays(1, &m_VAO);
		}

		void VertexArray::AddBuffer(ArrayBuffer * buffer, GLuint index)
		{
			// Bind this buffer
			Bind();
			// Bind the array buffer passed
			buffer->Bind();
			// Enable the indicated attribute on the vertex buffer
			glEnableVertexAttribArray(index);
			// Then set the vertex attributes pointers
			glVertexAttribPointer(index, buffer->GetComponentCount(), GL_FLOAT, GL_FALSE, 0, 0);
			// Add the buffers to the vector
			this->m_Buffers.push_back(buffer);
			// Unbind array buffer object
			buffer->Unbind();
			// Unbind this
			Unbind();			
		}

		void VertexArray::Bind() const
		{
			glBindVertexArray(m_VAO);
		}

		void VertexArray::Unbind() const
		{
			glBindVertexArray(0);
		}
	}
}