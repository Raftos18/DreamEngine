#include "Shader.h"

namespace dream
{
	namespace graphics
	{
		GLuint Shader::Load()
		{
			GLuint program = glCreateProgram();

			GLuint vertex = glCreateShader(GL_VERTEX_SHADER);
			GLuint fragment = glCreateShader(GL_FRAGMENT_SHADER);

			std::string vertSourceString = FileUtil::ReadFile(m_VertPath);
			std::string fragSourceString = FileUtil::ReadFile(m_FragPath);

			const char* vertSource = vertSourceString.c_str();
			const char* fragSource = fragSourceString.c_str();

			glShaderSource(vertex, 1, &vertSource, NULL);
			glCompileShader(vertex);

			GLint result;
			glGetShaderiv(vertex, GL_COMPILE_STATUS, &result);
			if (result == GL_FALSE)
			{
				GLint length;
				glGetShaderiv(vertex, GL_INFO_LOG_LENGTH, &length);
				std::vector<char> error(length);
				glGetShaderInfoLog(vertex, length, &length, &error[0]);
				std::cout << "Failed to complie vertex shader!" << std::endl << &error[0] << std::endl;
				glDeleteShader(vertex);
				return 0;
			}

			glShaderSource(fragment, 1, &fragSource, NULL);
			glCompileShader(fragment);

			glGetShaderiv(fragment, GL_COMPILE_STATUS, &result);
			if (result == GL_FALSE)
			{
				GLint length;
				glGetShaderiv(fragment, GL_INFO_LOG_LENGTH, &length);
				std::vector<char> error(length);
				glGetShaderInfoLog(fragment, length, &length, &error[0]);
				std::cout << "Failed to complie fragment shader!"<< std::endl << &error[0] << std::endl;
				glDeleteShader(vertex);
				return 0;
			}

			glAttachShader(program, vertex);
			glAttachShader(program, fragment);

			glLinkProgram(program);
			glValidateProgram(program);

			// Delete in the reverse order that you initialised
			glDeleteShader(fragment);
			glDeleteShader(vertex);

			return program;
		}

		GLint Shader::getUniformLocation(const GLchar * name)
		{
			return glGetUniformLocation(m_ShaderID, name);
		}

		Shader::Shader(const char * vertPath, const char * fragPath)
		{
			this->m_VertPath = vertPath;
			this->m_FragPath = fragPath;
			m_ShaderID = Load();
		}

		Shader::~Shader()
		{
			glDeleteProgram(m_ShaderID);
		}

		void Shader::SetUniform1f(const GLchar * name, float value)
		{
			glUniform1f(getUniformLocation(name), value);
		}

		void Shader::SetUniform1i(const GLchar * name, int value)
		{
			glUniform1f(getUniformLocation(name), value);
		}

		void Shader::SetUniform2f(const GLchar * name, maths::Vector2 & vector)
		{
			glUniform2f(getUniformLocation(name), vector.GetX(), vector.GetY());
		}

		void Shader::SetUniform3f(const GLchar * name, maths::Vector3 & vector)
		{
			glUniform3f(getUniformLocation(name), vector.GetX(), vector.GetY(), vector.GetZ());
		}

		void Shader::SetUniform4f(const GLchar * name, maths::Vector4 & vector)
		{
			glUniform4f(getUniformLocation(name), vector.GetX(), vector.GetY(), vector.GetZ(), vector.GetW());
		}

		void Shader::SetUniformMat4(const GLchar * name, const maths::Mat4x4 & matrix)
		{
			glUniformMatrix4fv(getUniformLocation(name), 1, GL_FALSE, matrix.m_Elements);
		}

		void dream::graphics::Shader::Enable() const
		{
			glUseProgram(m_ShaderID);
		}

		void dream::graphics::Shader::Disable() const
		{
			glUseProgram(0);
		}
	}
}


