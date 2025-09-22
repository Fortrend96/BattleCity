#include "Tank.h"

#include "../../Resources/ResourceManager.h"
#include "../../Renderer/Sprite.h"

CTank::CTank(const double fVelocity,
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
	, m_pSprite_respawn(CResourceManager::getSprite("respawn"))
	, m_spriteAnimator_respawn(m_pSprite_respawn)
	, m_pSprite_shield(CResourceManager::getSprite("shield"))
	, m_spriteAnimator_shield(m_pSprite_shield)
	, m_bMove(false)
	, m_fVelocity(fVelocity)
	, m_moveOffset(glm::vec2(0.f, 1.f))
	, m_bIsSpawning(true)
	, m_bHasShield(false)
{
	m_respawnTimer.setCallback(
		[&]()
		{
			m_bIsSpawning = false;
			m_bHasShield = true;
			m_shieldTimer.start(2000);
		}
	);

	m_respawnTimer.start(1500);

	m_shieldTimer.setCallback(
		[&]()
		{
			m_bHasShield = false;
		}
	);
}

void CTank::render() const
{
	if (m_bIsSpawning)
	{
		m_pSprite_respawn->render(m_position, m_size, m_fRotation, m_fLayer, m_spriteAnimator_respawn.getCurrentFrame());
	}
	else
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

		if (m_bHasShield)
		{
			m_pSprite_shield->render(m_position, m_size, m_fRotation, m_fLayer, m_spriteAnimator_shield.getCurrentFrame());
		}

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

void CTank::update(const double delta)
{
	if (m_bIsSpawning)
	{
		m_spriteAnimator_respawn.update(delta);
		m_respawnTimer.update(delta);
	}
	else
	{
		if (m_bHasShield)
		{
			m_spriteAnimator_shield.update(delta);
			m_shieldTimer.update(delta);
		}

		if (m_bMove)
		{
			m_position.x += static_cast<float>(delta * m_fVelocity * m_moveOffset.x);
			m_position.y += static_cast<float>(delta * m_fVelocity * m_moveOffset.y);

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
}
