#pragma once

#include "IGameObject.h"
#include <memory>


namespace RenderEngine {
	class CSprite;
}

class CBrickWall : public IGameObject
{
public:
	CBrickWall(const std::shared_ptr<RenderEngine::CSprite> pSprite, const glm::vec2& position, const glm::vec2& size, const float fRotation);
	virtual void render() const override;
	virtual void update(const uint64_t delta) override;

private:
	std::shared_ptr<RenderEngine::CSprite> m_pCurSprite;

};
