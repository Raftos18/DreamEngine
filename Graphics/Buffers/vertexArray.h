#pragma once

#include <GL/glew.h>
#include <vector>
#include "arrayBuffer.h"

namespace dream 
{
	namespace graphics
	{
		class VertexArray
		{
		private:
			GLuint						m_VAO;			// Holds the id of an OpenGL buffer(GL_VERTEX_ARRAY)
			std::vector<ArrayBuffer*>	m_Buffers;		// Holds pointers to the buffers assigned to this VertexArray
		public:
			// Default constructor. Generates a new vertex array buffer
			VertexArray();
			// Deletes the vertex array and clears the buffers stored
			~VertexArray();
			// Adds a new ArrayBuffer. 
			void AddBuffer(ArrayBuffer* buffer, GLuint index);
			// Bind the generated buffer to a GL_VERTEX_ARRAY
			void Bind() const;
			// Unbind the buffer for later use
			void Unbind() const;
		};
	}
}


