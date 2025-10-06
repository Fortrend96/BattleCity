#pragma once

#include "IGameObject.h"
#include "../../Renderer/SpriteAnimator.h"
#include "../../System/Timer.h"

#include <array>
#include <memory>

namespace RenderEngine {
    class CSprite;
}

class CBullet : public IGameObject {
public:

    enum class EOrientation : uint8_t 
    {
        Top,
        Bottom,
        Left,
        Right
    };

    CBullet(const double dVelocity, const glm::vec2& position, const glm::vec2& size, const glm::vec2& explosionSize, const float fLayer);
    virtual void render() const override;
    void update(const double delta) override;
    bool isActive() const { return m_bIsActive; }
    void fire(const glm::vec2& position, const glm::vec2& direction);
    virtual void onCollision() override;

private:
    glm::vec2 m_explosionSize;
    glm::vec2 m_explosionOffset;
    std::shared_ptr<RenderEngine::CSprite> m_pSprite_top;
    std::shared_ptr<RenderEngine::CSprite> m_pSprite_bottom;
    std::shared_ptr<RenderEngine::CSprite> m_pSprite_left;
    std::shared_ptr<RenderEngine::CSprite> m_pSprite_right;
    std::shared_ptr<RenderEngine::CSprite> m_pSprite_explosion;
    RenderEngine::CSpriteAnimator m_spriteAnimator_explosion;
    CTimer m_explosionTimer;
    EOrientation m_eOrientation;
    double m_maxVelocity;
    bool m_bIsActive;
    bool m_bIsExplosion;
};
