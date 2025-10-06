#pragma once

#include <glm/vec2.hpp>
#include <memory>

#include "IGameObject.h"
#include "../../Renderer/SpriteAnimator.h"
#include "../../System/Timer.h"
#include <string>

namespace RenderEngine {
    class Sprite;
}

class Bullet;

class Tank : public IGameObject {
public:

    enum class ETankType : uint8_t
    {
        Player1Yellow_type1,
        Player1Yellow_type2,
        Player1Yellow_type3,
        Player1Yellow_type4,

        Player2Green_type1,
        Player2Green_type2,
        Player2Green_type3,
        Player2Green_type4,

        EnemyWhite_type1,
        EnemyWhite_type2,
        EnemyWhite_type3,
        EnemyWhite_type4,

        EnemyGreen_type1,
        EnemyGreen_type2,
        EnemyGreen_type3,
        EnemyGreen_type4,

        EnemyRed_type1,
        EnemyRed_type2,
        EnemyRed_type3,
        EnemyRed_type4
    };

    static const std::array<std::string, 20> TankTypeToSpriteString;

    enum class EOrientation : uint8_t {
        Top,
        Bottom,
        Left,
        Right
    };

    Tank(const Tank::ETankType eType,
        const double maxVelocity,
        const glm::vec2& position,
        const glm::vec2& size,
        const float layer);

    void render() const override;
    void setOrientation(const EOrientation eOrientation);
    void update(const double delta) override;
    double getMaxVelocity() const { return m_maxVelocity; }
    void setVelocity(const double velocity) override;
    void fire();

private:
    EOrientation m_eOrientation;
    std::shared_ptr<Bullet> m_pCurrentBullet;
    std::shared_ptr<RenderEngine::Sprite> m_pSprite_top;
    std::shared_ptr<RenderEngine::Sprite> m_pSprite_bottom;
    std::shared_ptr<RenderEngine::Sprite> m_pSprite_left;
    std::shared_ptr<RenderEngine::Sprite> m_pSprite_right;
    RenderEngine::SpriteAnimator m_spriteAnimator_top;
    RenderEngine::SpriteAnimator m_spriteAnimator_bottom;
    RenderEngine::SpriteAnimator m_spriteAnimator_left;
    RenderEngine::SpriteAnimator m_spriteAnimator_right;

    std::shared_ptr<RenderEngine::Sprite> m_pSprite_respawn;
    RenderEngine::SpriteAnimator m_spriteAnimator_respawn;

    std::shared_ptr<RenderEngine::Sprite> m_pSprite_shield;
    RenderEngine::SpriteAnimator m_spriteAnimator_shield;

    Timer m_respawnTimer;
    Timer m_shieldTimer;

    double m_maxVelocity;
    bool m_isSpawning;
    bool m_hasShield;

    static const std::string& getTankSpriteFromType(const ETankType eType);
};