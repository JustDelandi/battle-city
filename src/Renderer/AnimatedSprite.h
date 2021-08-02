#pragma once

#include "sprite.h"

#include <map>
#include <vector>
#include <stdint.h>

namespace RenderEngine
{
	class AnimatedSprite : public Sprite
	{
	public:
		AnimatedSprite(std::shared_ptr<Texture2D> pTexture,
			std::string initialSubTexture,
			std::shared_ptr<ShaderProgram> pShaderProgram);
	public:
		void insertState(const std::string& state, std::vector < std::pair<std::string, uint64_t>> subTexturesDuration);
		void render(const glm::vec2& position, const glm::vec2& size, const float rotation) const override;
		void update(const uint64_t delta);
		void setState(const std::string& newState);
	private:
		std::map<std::string, std::vector<std::pair<std::string, uint64_t>>> m_statesMap;
		size_t m_currentFrame = 0;
		uint64_t m_currentAnimationTime = 0;
		std::map<std::string, std::vector<std::pair<std::string, uint64_t>>>::const_iterator m_pCurrentAnimationDurations;
		mutable bool m_dirty = false;
	};
}