#pragma once

#include<string>
#include<memory>
#include<map>
#include <vector>

namespace RenderEngine
{
	class ShaderProgram;
	class Texture2D;
	class Sprite;
	class AnimatedSprite;
}

class ResourceManager
{
public:
	//ResourceManager(const std::string& executablePath);
	static void setExecutablePath(const std::string& executablePath);
	static void unloadAllResources();
public:
	~ResourceManager() = delete;
	ResourceManager() = delete;
	ResourceManager(const ResourceManager&) = delete;
	ResourceManager& operator=(const ResourceManager&) = delete;
	ResourceManager& operator=(ResourceManager&&) = delete;
	ResourceManager(ResourceManager&&) = delete;
public: // metods for shaders 
	static std::shared_ptr<RenderEngine::ShaderProgram> loadShaders(const std::string& shaderName, const std::string& vertexPath, const std::string& fragmentPath);
	static std::shared_ptr<RenderEngine::ShaderProgram> getShaderProgram(const std::string& shaderName);
public: // metods for textures
	static std::shared_ptr<RenderEngine::Texture2D> loadTexture(const std::string& textureName, const std::string& texturePath);
	static std::shared_ptr<RenderEngine::Texture2D> getTextures(const std::string& textureName);
public: //metods for sprites
	static std::shared_ptr<RenderEngine::Sprite> loadSprite(const std::string& spriteName,
											 	 const std::string& textureName,
												 const std::string& shaderName,
												 const std::string& subTextureName = "default");
	static std::shared_ptr<RenderEngine::Sprite> getSprite(const std::string& spriteName);
public: //metods for subTextures
	static std::shared_ptr<RenderEngine::Texture2D> loadTextureAtlas(const std::string textureName,
														  const std::string texturePath,
													      const std::vector<std::string> subTextures,
														  const unsigned int subTextureWidth,
														  const unsigned int subTextureHeight);
public: //metods for animated sprites
	static std::shared_ptr<RenderEngine::AnimatedSprite> loadAnimatedSprite(const std::string& spriteName,
		const std::string& textureName,
		const std::string& shaderName,
		const std::string& subTextureName = "default");
	static std::shared_ptr<RenderEngine::AnimatedSprite> getAnimatedSprite(const std::string& spriteName);
public: // for rapid json
	static bool loadJSONResources(const std::string& JSONPath);

	static const std::vector<std::vector<std::string>>& getLevels() { return m_levels; };
private:
	typedef std::map < const std::string, std::shared_ptr<RenderEngine::ShaderProgram>> ShaderProgramsMap;
	static ShaderProgramsMap m_shaderPrograms;

	static std::string m_path;

	typedef std::map< const std::string, std::shared_ptr<RenderEngine::Texture2D>> TexturesMap;
	static TexturesMap m_textures;

	typedef std::map< const std::string, std::shared_ptr<RenderEngine::Sprite>> SpritesMap;
	static SpritesMap m_sprites;

	typedef std::map< const std::string, std::shared_ptr<RenderEngine::AnimatedSprite>> AnimatedSpritesMap;
	static AnimatedSpritesMap m_animatedSprites;

	static std::vector<std::vector<std::string>> m_levels;
private:
	static std::string getFileString(const std::string& relativeFilePath);
};