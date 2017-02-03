#pragma once

#include <GL\glew.h>

namespace dream
{
	namespace graphics
	{
		class IndexBuffer
		{
		private:
			GLuint m_BufferID;
			GLuint m_Count;

		public:
			IndexBuffer(GLushort* data, GLsizei count);
			IndexBuffer(GLuint* data, GLsizei count);
			~IndexBuffer();

			void Bind() const;
			void Unbind() const;

			inline GLuint GetCount() const { return m_Count; }
		};
	}
}