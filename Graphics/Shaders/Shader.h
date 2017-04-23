#pragma once

// Include OpenGL
#include <GL\glew.h>
// Include Std.
#include <string>
// Include Dream
#include "..\..\Math\maths.h"

namespace dream
{
	namespace graphics 
	{
		class Shader
		{	
		private:
			GLuint m_ShaderProgram;			// The id of the created gl shader program
			GLuint m_VertexShader;			// Holds the vertex shader id
			GLuint m_FragmentShader;		// Holds the fragment shader id
		private:			
			// Initializes the shader object. Returns a OpenGL shader id
			GLuint Init(std::string vertFilename, std::string fragFilename);
			// Creates a shader program provided the source code (GLSL) 
			// and the shader type(GL_VERTEX_SHADER or GL_FRAGMENT_SHADER)
			// and returns their id.
			GLuint CreateShader(std::string shaderSource, int shaderType);
			// Creates a new OpenGL shader program and links it with the provided shaders
			GLuint CreateAndLinkProgram(GLuint vertexShader, GLuint fragmentShader);
			// Returns the id of a uniform (GLSL) from the current shader program given its name
			GLint GetUniformLocation(const GLchar* name);
		public:
			Shader(std::string vertFilename, std::string fragFilename);
			virtual ~Shader();

			// Returns the id of the shader program
			GLuint Get() const { return m_ShaderProgram; }
			// Sets a float uniform (GLSL) variable specified by name
			void SetUniform1f(const GLchar* name, float value);
			// Sets a float array uniform (GLSL) variable specified by name
			void SetUniform1fv(const GLchar* name, int count, float* value);
			// Sets a integer uniform (GLSL) variable specified by name
			void SetUniform1i(const GLchar* name, int value);
			// Sets a integer array uniform (GLSL) variable specified by name
			void SetUniform1iv(const GLchar* name, GLsizei count, int* value);
			// Sets a Vector2 of floats uniform (GLSL) variable specified by name
			void SetUniform2f(const GLchar* name, maths::Vector2& vector);
			// Sets a Vector3 of floats uniform (GLSL) variable specified by name
			void SetUniform3f(const GLchar* name, maths::Vector3& vector);
			// Sets a Vector4 of floats uniform (GLSL) variable specified by name
			void SetUniform4f(const GLchar* name, maths::Vector4& vector);
			// Sets a 4x4 Matrix uniform (GLSL) variable specified by name
			void SetUniformMat4(const GLchar* name, const maths::Mat4x4& matrix);

			// Enables the shader 
			void Enable() const;
			// Disables the shader
			void Disable() const;
		};		
	}
}

