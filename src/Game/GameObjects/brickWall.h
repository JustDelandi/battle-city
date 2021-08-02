#pragma once

#include "iGameObject.h"
#include <memory>

namespace RenderEngine
{
	class Sprite;
}

class BrickWall : public IGameObject
{
public:
	BrickWall(std::shared_ptr<RenderEngine::Sprite> pSprite, const glm::vec2& position, const glm::vec2& size, const float rotation);
	virtual void render() const override;
	virtual void update(const uint64_t delta) override;
private:
	std::shared_ptr<RenderEngine::Sprite> m_pCurrentSprite;
};