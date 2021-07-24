#pragma once

#include<string>
#include<memory>
#include<map>

namespace Renderer
{
	class ShaderProgram;
	class Texture2D;
}

class ResourceManager
{
public:
	ResourceManager(const std::string& executablePath);
	~ResourceManager() = default;
public:
	ResourceManager(const ResourceManager&) = delete;
	ResourceManager& operator=(const ResourceManager&) = delete;
	ResourceManager& operator=(ResourceManager&&) = delete;
	ResourceManager(ResourceManager&&) = delete;
public: // metods for shaders 
	std::shared_ptr<Renderer::ShaderProgram> loadShaders(const std::string& shaderName, const std::string& vertexPath, const std::string& fragmentPath);
	std::shared_ptr<Renderer::ShaderProgram> getShaderProgram(const std::string& shaderName);
public: // metods for textures
	std::shared_ptr<Renderer::Texture2D> loadTexture(const std::string& textureName, const std::string& texturePath);
	std::shared_ptr<Renderer::Texture2D> getTextures(const std::string& textureName) const;

private:
	typedef std::map < const std::string, std::shared_ptr<Renderer::ShaderProgram>> ShaderProgramsMap;
	ShaderProgramsMap m_shaderPrograms;

	std::string m_path;

	typedef std::map< const std::string, std::shared_ptr<Renderer::Texture2D>> TexturesMap;
	TexturesMap m_textures;
private:
	std::string getFileString(const std::string& relativeFilePath) const;
};