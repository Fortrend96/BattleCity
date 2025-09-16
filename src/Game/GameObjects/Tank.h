#pragma once
#include <glm/vec2.hpp>
#include <memory>

#include "IGameObject.h"
#include "../../Renderer/SpriteAnimator.h"

namespace RenderEngine 
{
	class CSprite;
}

class CTank : public IGameObject
{
public:
	enum class EOrientation {
		Top,
		Bottom,
		Left,
		Right
	};

	CTank(std::shared_ptr<RenderEngine::CSprite> pSprite_top, 
		std::shared_ptr<RenderEngine::CSprite> pSprite_bottom,
		std::shared_ptr<RenderEngine::CSprite> pSprite_left,
		std::shared_ptr<RenderEngine::CSprite> pSprite_right,
		const float fVelocity,
		const glm::vec2& position, 
		const glm::vec2& size);

	void render() const override;
	void setOrientaion(const EOrientation eOrientation);

	void move(const bool bMove);
	void update(const uint64_t delta) override;

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

	bool m_bMove;
	float m_fVelocity;
	glm::vec2 m_moveOffset;

};
