#include "Border.h"

#include "../../Resources/ResourceManager.h"
#include "../../Renderer/Sprite.h"

CBorder::CBorder(const glm::vec2& position, const glm::vec2& size, const float rotation, const float fLayer)
    : IGameObject(IGameObject::EObjectType::Border, position, size, rotation, fLayer)
    , m_sprite(CResourceManager::getSprite("border"))
{
    m_colliders.emplace_back(glm::vec2(0), m_size);
}

void CBorder::render() const
{
    m_sprite->render(m_position, m_size, m_fRotation, m_fLayer);
}