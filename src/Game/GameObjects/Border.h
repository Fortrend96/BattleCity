#pragma once

#include "IGameObject.h"

#include <array>
#include <memory>

namespace RenderEngine {
    class CSprite;
}

class CBorder : public IGameObject {
public:

    CBorder(const glm::vec2& position, const glm::vec2& size, const float rotation, const float fLayer);
    virtual void render() const override;

private:
    std::shared_ptr<RenderEngine::CSprite> m_sprite;
};