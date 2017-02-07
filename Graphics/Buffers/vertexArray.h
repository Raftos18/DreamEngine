#pragma once

#include <GL/glew.h>
#include <vector>
#include "buffer.h"

namespace dream 
{
	namespace graphics
	{
		class VertexArray
		{
		private:
			GLuint m_ArrayID;
			// Nobody uses raw pointer anymore. Too old
			std::vector<Buffer*> m_Buffers;
		public:
			VertexArray();
			~VertexArray();
			void AddBuffer(Buffer* buffer, GLuint index);
			void Bind() const;
			void Unbind() const;
		};
	}
}


