#include "Tank.h"
#include "../../Renderer/AnimatedSprite.h"

CTank::CTank(std::shared_ptr<RenderEngine::CAnimatedSprite> pSprite, const float fVelocity,
	const glm::vec2& position, const glm::vec2& size):
					IGameObject(position,size, 0),
					m_eOrientation(EOrientation::Top),
					m_pSprite(std::move(pSprite)),
					m_bMove(false),
					m_fVelocity(fVelocity),
					m_moveOffset(glm::vec2(0.f,1.f))
{
}

void CTank::render() const
{
	m_pSprite->render(m_position, m_size, m_fRotation);
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
		m_pSprite->setState("tankTopState");
		m_moveOffset.x = 0.f;
		m_moveOffset.y = 1.f;
		break;
	case CTank::EOrientation::Bottom:
		m_pSprite->setState("tankBottomState");
		m_moveOffset.x = 0.f;
		m_moveOffset.y = -1.f;
		break;
	case CTank::EOrientation::Left:
		m_pSprite->setState("tankLeftState");
		m_moveOffset.x = -1.f;
		m_moveOffset.y = 0.f;
		break;
	case CTank::EOrientation::Right:
		m_pSprite->setState("tankRightState");
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
		m_pSprite->update(delta);
	}
}
