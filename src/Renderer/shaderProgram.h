#pragma once

#include <string>
#include <glad/glad.h>
#include <glm/mat4x4.hpp>

namespace RenderEngine
{

	class ShaderProgram
	{
	public:
		ShaderProgram(const std::string& vertexShader, const std::string& fragmentShader);
		~ShaderProgram();
	public:
		ShaderProgram() = delete;
		ShaderProgram(const ShaderProgram&) = delete;
		ShaderProgram(ShaderProgram&) = delete;
		ShaderProgram& operator=(const ShaderProgram&) = delete;
	public:
		ShaderProgram& operator=(ShaderProgram&& shaderProgram) noexcept;
		ShaderProgram(ShaderProgram&& shaderProgram) noexcept;
	public:
		bool isCompiled() const { return m_isCompiled; }
		void use() const;
		void setInt(const std::string& name, const GLint value); // set uniform for fragment shader
		void setMatrix4(const std::string& name, const glm::mat4& matrix);//set uniform for shader;
	private:
		bool m_isCompiled = false;
		GLuint m_ID = 0;
	private:
		bool createShader(const std::string& source, const GLenum shaderType, GLuint& shaderID);
	};
}