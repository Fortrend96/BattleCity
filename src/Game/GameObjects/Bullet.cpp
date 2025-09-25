#include "Bullet.h"

#include "../../Resources/ResourceManager.h"
#include "../../Renderer/Sprite.h"

CBullet::CBullet(const double dVelocity, const glm::vec2& position, const glm::vec2& size, const float fLayer)
    : IGameObject(position, size, 0.f, fLayer)
    , m_pSprite_top(CResourceManager::getSprite("bullet_Top"))
    , m_pSprite_bottom(CResourceManager::getSprite("bullet_Bottom"))
    , m_pSprite_left(CResourceManager::getSprite("bullet_Left"))
    , m_pSprite_right(CResourceManager::getSprite("bullet_Right"))
    , m_eOrientation(EOrientation::Top)
    , m_bIsActive(false)
{
    setVelocity(dVelocity);
    m_colliders.emplace_back(glm::vec2(0), m_size);
}

void CBullet::render() const
{
    switch (m_eOrientation)
    {
    case EOrientation::Top:
        m_pSprite_top->render(m_position, m_size, m_fRotation, m_fLayer);
        break;
    case EOrientation::Bottom:
        m_pSprite_bottom->render(m_position, m_size, m_fRotation, m_fLayer);
        break;
    case EOrientation::Left:
        m_pSprite_left->render(m_position, m_size, m_fRotation, m_fLayer);
        break;
    case EOrientation::Right:
        m_pSprite_right->render(m_position, m_size, m_fRotation, m_fLayer);
        break;
    }
}

void CBullet::fire(const glm::vec2& position, const glm::vec2& direction)
{
    m_position = position;
    m_direction = direction;
    if (m_direction.x == 0.f)
    {
        m_eOrientation = (m_direction.y < 0) ? EOrientation::Bottom : EOrientation::Top;
    }
    else
    {
        m_eOrientation = (m_direction.x < 0) ? EOrientation::Left : EOrientation::Right;
    }
    m_bIsActive = true;
}
