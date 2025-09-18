#pragma once

#include "IGameObject.h"

#include <array>
#include <memory>

namespace RenderEngine {
    class CSprite;
}

class CIce : public IGameObject {
public:

    enum class EBlockLocation : uint8_t {
        TopLeft,
        TopRight,
        BottomLeft,
        BottomRight
    };

    CIce(const glm::vec2& position, const glm::vec2& size, const float rotation, const float fLayer);
    virtual void render() const override;

private:
    void renderBlock(const EBlockLocation eBlockLocation) const;

    std::shared_ptr<RenderEngine::CSprite> m_sprite;
    std::array<glm::vec2, 4> m_blockOffsets;
};