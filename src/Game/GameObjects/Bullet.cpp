#include "Bullet.h"

#include "../../Resources/ResourceManager.h"
#include "../../Renderer/Sprite.h"

CBullet::CBullet(const double dVelocity, const glm::vec2& position, const glm::vec2& size, const glm::vec2& explosionSize, const float fLayer)
    : IGameObject(IGameObject::EObjectType::Bullet, position, size, 0.f, fLayer)
    , m_explosionSize(explosionSize)
    , m_explosionOffset((m_explosionSize - m_size) / 2.f)
    , m_pSprite_top(CResourceManager::getSprite("bullet_Top"))
    , m_pSprite_bottom(CResourceManager::getSprite("bullet_Bottom"))
    , m_pSprite_left(CResourceManager::getSprite("bullet_Left"))
    , m_pSprite_right(CResourceManager::getSprite("bullet_Right"))
    , m_pSprite_explosion(CResourceManager::getSprite("explosion"))
    , m_spriteAnimator_explosion(m_pSprite_explosion)
    , m_eOrientation(EOrientation::Top)
    , m_maxVelocity(dVelocity)
    , m_bIsActive(false)
    , m_bIsExplosion(false)
{
    m_colliders.emplace_back(glm::vec2(0), m_size);

    m_explosionTimer.setCallback([&]()
        {
            m_bIsExplosion = false;
            m_bIsActive = false;
        }
    );
}

void CBullet::render() const
{
    if (m_bIsActive)
    {
        if (m_bIsExplosion)
        {
            switch (m_eOrientation)
            {
            case EOrientation::Top:
                m_pSprite_explosion->render(m_position - m_explosionOffset + glm::vec2(0, m_size.y / 2.f), m_explosionSize, m_fRotation, m_fLayer + 0.1f, m_spriteAnimator_explosion.getCurrentFrame());
                break;
            case EOrientation::Bottom:
                m_pSprite_explosion->render(m_position - m_explosionOffset - glm::vec2(0, m_size.y / 2.f), m_explosionSize, m_fRotation, m_fLayer + 0.1f, m_spriteAnimator_explosion.getCurrentFrame());
                break;
            case EOrientation::Left:
                m_pSprite_explosion->render(m_position - m_explosionOffset - glm::vec2(m_size.x / 2.f, 0), m_explosionSize, m_fRotation, m_fLayer + 0.1f, m_spriteAnimator_explosion.getCurrentFrame());
                break;
            case EOrientation::Right:
                m_pSprite_explosion->render(m_position - m_explosionOffset + glm::vec2(m_size.x / 2.f, 0), m_explosionSize, m_fRotation, m_fLayer + 0.1f, m_spriteAnimator_explosion.getCurrentFrame());
                break;
            }
        }
        else
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
    }
}

void CBullet::update(const double delta)
{
    if (m_bIsExplosion)
    {
        m_spriteAnimator_explosion.update(delta);
        m_explosionTimer.update(delta);
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

    setVelocity(m_maxVelocity);
}

void CBullet::onCollision()
{
    setVelocity(0);
    m_bIsExplosion = true;
    m_spriteAnimator_explosion.reset();
    m_explosionTimer.start(m_spriteAnimator_explosion.getTotalDuration());
}
