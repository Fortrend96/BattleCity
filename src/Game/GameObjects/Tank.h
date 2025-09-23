#pragma once
#include <glm/vec2.hpp>
#include <memory>

#include "IGameObject.h"
#include "../../Renderer/SpriteAnimator.h"
#include "../../System/Timer.h"

namespace RenderEngine 
{
	class CSprite;
}

class CTank : public IGameObject
{
public:
	enum class EOrientation : uint8_t {
		Top,
		Bottom,
		Left,
		Right
	};

	CTank(const double dMaxVelocity,
		const glm::vec2& position,
		const glm::vec2& size, const float fLayer);

	void render() const override;
	void setOrientaion(const EOrientation eOrientation);

	void update(const double delta) override;

	double getMaxVelocity() const { return m_dMaxVelocity; }

	void setVelocity(const double dVelocity) override;

private:
	EOrientation m_eOrientation;

	std::shared_ptr<RenderEngine::CSprite> m_pSprite_top;
	std::shared_ptr<RenderEngine::CSprite> m_pSprite_bottom;
	std::shared_ptr<RenderEngine::CSprite> m_pSprite_left;
	std::shared_ptr<RenderEngine::CSprite> m_pSprite_right;

	RenderEngine::CSpriteAnimator m_spriteAnimator_top;
	RenderEngine::CSpriteAnimator m_spriteAnimator_bottom;
	RenderEngine::CSpriteAnimator m_spriteAnimator_left;
	RenderEngine::CSpriteAnimator m_spriteAnimator_right;


	std::shared_ptr<RenderEngine::CSprite> m_pSprite_respawn;
	RenderEngine::CSpriteAnimator m_spriteAnimator_respawn;

	std::shared_ptr<RenderEngine::CSprite> m_pSprite_shield;
	RenderEngine::CSpriteAnimator m_spriteAnimator_shield;

	CTimer m_respawnTimer;
	CTimer m_shieldTimer;

	double m_dMaxVelocity;
	bool m_bIsSpawning;
	bool m_bHasShield;


};
