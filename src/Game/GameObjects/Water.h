#pragma once

#include "IGameObject.h"
#include "../../Renderer/SpriteAnimator.h"

#include <array>
#include <memory>

namespace RenderEngine {
    class CSprite;
}

class CWater : public IGameObject {
public:

    enum class EBlockLocation : uint8_t {
        TopLeft,
        TopRight,
        BottomLeft,
        BottomRight
    };

    CWater(const glm::vec2& position, const glm::vec2& size, const float rotation);
    virtual void render() const override;
    void update(const uint64_t delta) override;

private:
    void renderBlock(const EBlockLocation eBlockLocation) const;

    std::shared_ptr<RenderEngine::CSprite> m_sprite;
    RenderEngine::CSpriteAnimator m_spriteAnimator;
    std::array<glm::vec2, 4> m_blockOffsets;
};