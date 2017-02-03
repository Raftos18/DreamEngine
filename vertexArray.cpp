#include "vertexArray.h"

namespace dream
{
	namespace graphics
	{
		dream::graphics::VertexArray::VertexArray()
		{
			glGenVertexArrays(1, &m_ArrayID);
		}

		dream::graphics::VertexArray::~VertexArray()
		{
			for (size_t i = 0; i < m_Buffers.size(); i++)
				delete m_Buffers[i];

			glDeleteVertexArrays(1, &m_ArrayID);
		}

		void dream::graphics::VertexArray::AddBuffer(Buffer * buffer, GLuint index)
		{
			Bind();
			buffer->Bind();
			glEnableVertexAttribArray(index);

			glVertexAttribPointer(index, buffer->GetComponentCount(), GL_FLOAT, GL_FALSE, 0, 0);
			this->m_Buffers.push_back(buffer);

			buffer->Unbind();
			Unbind();
		}

		void dream::graphics::VertexArray::Bind() const
		{
			glBindVertexArray(m_ArrayID);
		}

		void dream::graphics::VertexArray::Unbind() const
		{
			glBindVertexArray(0);
		}
	}
}