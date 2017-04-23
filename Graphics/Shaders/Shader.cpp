// Include Std
#include <iostream>
#include <vector>
// Include Dream
#include "shader.h"
#include "../../Utils/dreamUtils.h"

namespace dream
{
	namespace graphics
	{
		Shader::Shader(std::string vertFilename, std::string fragFilename)
		{
			m_ShaderProgram = Init(vertFilename, fragFilename);
		}

		Shader::~Shader()
		{
			glDeleteProgram(m_ShaderProgram);
		}

		GLuint Shader::Init(std::string vertFilename, std::string fragFilename)
		{			
			GLuint shaderProgram;

			// Read the vertex source code from the file and save to string
			std::string vertSourceString = utilities::File::ReadFile(vertFilename.c_str());
			// Read the vertex source code from the file and save to string
			std::string fragSourceString = utilities::File::ReadFile(fragFilename.c_str());
			
			// Create shaders and save the id
			m_VertexShader = CreateShader(vertSourceString, GL_VERTEX_SHADER);
			m_FragmentShader = CreateShader(fragSourceString, GL_FRAGMENT_SHADER);
			// Create shader program and save the id
			shaderProgram = CreateAndLinkProgram(m_VertexShader, m_FragmentShader);
			
			return shaderProgram;
		}

		GLuint Shader::CreateShader(std::string shaderSource, int shaderType)
		{
			// Build and compile our shader program
			GLuint shader = glCreateShader(shaderType);
			const GLchar* source = shaderSource.c_str();
			glShaderSource(shader, 1, &source, NULL);
			glCompileShader(shader);

			// Check for errors
			GLint success;
			GLchar infoLog[512];
			glGetShaderiv(shader, GL_COMPILE_STATUS, &success);

			if (!success) {
				glGetShaderInfoLog(shader, 512, NULL, infoLog);
				if (shaderType == GL_VERTEX_SHADER)
					std::cout << "[Shader] Vertex shader failed to compile\n" << infoLog << std::endl;
				else if (shaderType == GL_FRAGMENT_SHADER)
					std::cout << "[Shader] Fragment shader failed to compile\n" << infoLog << std::endl;
			}
			return shader;
		}


		GLuint Shader::CreateAndLinkProgram(GLuint vertexShader, GLuint fragmentShader)
		{					
			// Create and link program with shaders
			GLuint shaderProgram = glCreateProgram();
			glAttachShader(shaderProgram, vertexShader);
			glAttachShader(shaderProgram, fragmentShader);
			glLinkProgram(shaderProgram);

			// Check for linking errors
			GLint success;
			GLchar infoLog[512];
			glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
			if (!success) {
				glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
				std::cout << "[Shader] Shader program failed to link\n" << infoLog << std::endl;
			}

			// Fragment and Vertex shaders no longer needed as 
			// they are linked to one program so delete them
			glDeleteShader(vertexShader);
			glDeleteShader(fragmentShader);

			return shaderProgram;
		}

		GLint Shader::GetUniformLocation(const GLchar * name)
		{
			return glGetUniformLocation(m_ShaderProgram, name);
		}

		void Shader::SetUniform1f(const GLchar * name, float value)
		{
			glUniform1f(GetUniformLocation(name), value);
		}

		void Shader::SetUniform1fv(const GLchar * name, int count, float * value)
		{
			glUniform1fv(GetUniformLocation(name), count, value);
		}		

		void Shader::SetUniform1iv(const GLchar * name, GLsizei count, int* value)
		{
			glUniform1iv(GetUniformLocation(name), count, value);
		}

		void Shader::SetUniform1i(const GLchar * name, int value)
		{
			glUniform1f(GetUniformLocation(name), value);
		}

		void Shader::SetUniform2f(const GLchar * name, maths::Vector2 & vector)
		{
			glUniform2f(GetUniformLocation(name), vector.GetX(), vector.GetY());
		}

		void Shader::SetUniform3f(const GLchar * name, maths::Vector3 & vector)
		{
			glUniform3f(GetUniformLocation(name), vector.GetX(), vector.GetY(), vector.GetZ());
		}

		void Shader::SetUniform4f(const GLchar * name, maths::Vector4 & vector)
		{
			glUniform4f(GetUniformLocation(name), vector.GetX(), vector.GetY(), vector.GetZ(), vector.GetW());
		}

		void Shader::SetUniformMat4(const GLchar * name, const maths::Mat4x4 & matrix)
		{
			glUniformMatrix4fv(GetUniformLocation(name), 1, GL_FALSE, matrix.m_Elements);
		}

		void dream::graphics::Shader::Enable() const
		{
			glUseProgram(m_ShaderProgram);
		}

		void dream::graphics::Shader::Disable() const
		{
			glUseProgram(0);
		}
	}
}


