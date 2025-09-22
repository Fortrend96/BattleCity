#include "Border.h"

#include "../../Resources/ResourceManager.h"
#include "../../Renderer/Sprite.h"

CBorder::CBorder(const glm::vec2& position, const glm::vec2& size, const float rotation, const float fLayer)
    : IGameObject(position, size, rotation, fLayer)
    , m_sprite(CResourceManager::getSprite("border"))
{
}

void CBorder::render() const
{
    m_sprite->render(m_position, m_size, m_fRotation, m_fLayer);
}