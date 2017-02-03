#pragma once

#include <GL\glew.h>
#include "fileUtil.h"
#include <iostream>
#include <vector>
#include "maths.h"

namespace dream
{
	namespace graphics 
	{
		class Shader
		{
		private:
			const char* m_VertPath;
			const char* m_FragPath;

			GLuint Load();
			GLint getUniformLocation(const GLchar* name);
		public:
			GLuint m_ShaderID;
			Shader(const char* vertPath, const char* fragPath);
			~Shader();

			inline GLuint Get() const { return m_ShaderID; }
			
			void SetUniform1f(const GLchar* name, float value);
			void SetUniform1i(const GLchar* name, int value);
			void SetUniform2f(const GLchar* name, maths::Vector2& vector);
			void SetUniform3f(const GLchar* name, maths::Vector3& vector);
			void SetUniform4f(const GLchar* name, maths::Vector4& vector);
			void SetUniformMat4(const GLchar* name, const maths::Mat4x4& matrix);


			void Enable() const;
			void Disable() const;
		};
	}
}

