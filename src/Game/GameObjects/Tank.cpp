#include "Tank.h"

#include "../../Resources/ResourceManager.h"
#include "../../Renderer/Sprite.h"

CTank::CTank(const float fVelocity,
	const glm::vec2& position,
	const glm::vec2& size, const float fLayer)
	: IGameObject(position, size, 0.f, fLayer)
	, m_eOrientation(EOrientation::Top)
	, m_pSprite_top(CResourceManager::getSprite("tankSprite_top"))
	, m_pSprite_bottom(CResourceManager::getSprite("tankSprite_bottom"))
	, m_pSprite_left(CResourceManager::getSprite("tankSprite_left"))
	, m_pSprite_right(CResourceManager::getSprite("tankSprite_right"))
	, m_spriteAnimator_top(m_pSprite_top)
	, m_spriteAnimator_bottom(m_pSprite_bottom)
	, m_spriteAnimator_left(m_pSprite_left)
	, m_spriteAnimator_right(m_pSprite_right)
	, m_bMove(false)
	, m_fVelocity(fVelocity)
	, m_moveOffset(glm::vec2(0.f, 1.f))
{
}

void CTank::render() const
{
	switch (m_eOrientation)
	{
	case CTank::EOrientation::Top:
		m_pSprite_top->render(m_position, m_size, m_fRotation, m_fLayer, m_spriteAnimator_top.getCurrentFrame());
		break;
	case CTank::EOrientation::Bottom:
		m_pSprite_bottom->render(m_position, m_size, m_fRotation, m_fLayer, m_spriteAnimator_bottom.getCurrentFrame());
		break;
	case CTank::EOrientation::Left:
		m_pSprite_left->render(m_position, m_size, m_fRotation, m_fLayer, m_spriteAnimator_left.getCurrentFrame());
		break;
	case CTank::EOrientation::Right:
		m_pSprite_right->render(m_position, m_size, m_fRotation, m_fLayer, m_spriteAnimator_right.getCurrentFrame());
		break;
	}
}

void CTank::setOrientaion(const EOrientation eOrientation)
{
	if (m_eOrientation == eOrientation)
	{
		return;
	}

	m_eOrientation = eOrientation;

	switch (m_eOrientation)
	{
	case CTank::EOrientation::Top:
		m_moveOffset.x = 0.f;
		m_moveOffset.y = 1.f;
		break;
	case CTank::EOrientation::Bottom:
		m_moveOffset.x = 0.f;
		m_moveOffset.y = -1.f;
		break;
	case CTank::EOrientation::Left:
		m_moveOffset.x = -1.f;
		m_moveOffset.y = 0.f;
		break;
	case CTank::EOrientation::Right:
		m_moveOffset.x = 1.f;
		m_moveOffset.y = 0.f;
		break;
	default:
		break;
	}
}

void CTank::move(const bool bMove)
{
	m_bMove = bMove;
}

void CTank::update(const uint64_t delta)
{
	if (m_bMove)
	{
		m_position += delta * m_fVelocity * m_moveOffset;

		switch (m_eOrientation) 
		{
		case CTank::EOrientation::Top:
			m_spriteAnimator_top.update(delta);
			break;
		case CTank::EOrientation::Bottom:
			m_spriteAnimator_bottom.update(delta);
			break;
		case CTank::EOrientation::Left:
			m_spriteAnimator_left.update(delta);
			break;
		case CTank::EOrientation::Right:
			m_spriteAnimator_right.update(delta);
			break;
		}

	}
}
