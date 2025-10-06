#include "Tank.h"

#include "../../Resources/ResourceManager.h"
#include "../../Renderer/Sprite.h"
#include "Bullet.h"
#include "../../Physics/PhysicsEngine.h"

CTank::CTank(const double dMaxVelocity,
	const glm::vec2& position,
	const glm::vec2& size, const float fLayer)
	: IGameObject(IGameObject::EObjectType::Tank, position, size, 0.f, fLayer)
	, m_eOrientation(EOrientation::Top)
	, m_pCurrentBullet(std::make_shared<CBullet>(0.1, m_position + m_size / 4.f, m_size / 2.f, m_size, fLayer))
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
	, m_dMaxVelocity(dMaxVelocity)
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

	m_colliders.emplace_back(glm::vec2(0), m_size);

	Physics::CPhysicsEngine::addDynamicGameObject(m_pCurrentBullet);
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
			m_pSprite_shield->render(m_position, m_size, m_fRotation, m_fLayer + 0.1f, m_spriteAnimator_shield.getCurrentFrame());
		}

		if (m_pCurrentBullet->isActive())
		{
			m_pCurrentBullet->render();
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
		m_direction.x = 0.f;
		m_direction.y = 1.f;
		break;
	case CTank::EOrientation::Bottom:
		m_direction.x = 0.f;
		m_direction.y = -1.f;
		break;
	case CTank::EOrientation::Left:
		m_direction.x = -1.f;
		m_direction.y = 0.f;
		break;
	case CTank::EOrientation::Right:
		m_direction.x = 1.f;
		m_direction.y = 0.f;
		break;
	}
}

void CTank::setVelocity(const double dVelocity)
{
	if (!m_bIsSpawning)
	{
		m_dVelocity = dVelocity;
	}
}

void CTank::update(const double delta)
{
	if (m_pCurrentBullet->isActive())
	{
		m_pCurrentBullet->update(delta);
	}

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

		if (m_dVelocity > 0)
		{
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

void CTank::fire()
{
	if (!m_bIsSpawning && !m_pCurrentBullet->isActive())
	{
		m_pCurrentBullet->fire(m_position + m_size / 4.f + m_size * m_direction / 4.f, m_direction);
	}
}


