#include "Trees.h"

#include "../../Resources/ResourceManager.h"
#include "../../Renderer/Sprite.h"

CTrees::CTrees(const glm::vec2& position, const glm::vec2& size, const float rotation, const float fLayer)
    : IGameObject(IGameObject::EObjectType::Trees, position, size, rotation, fLayer)
    , m_sprite(CResourceManager::getSprite("trees"))
    , m_blockOffsets{ glm::vec2(0, m_size.y / 2.f),
                       glm::vec2(m_size.x / 2.f, m_size.y / 2.f),
                       glm::vec2(0, 0),
                       glm::vec2(m_size.x / 2.f, 0) }
{
}

void CTrees::renderBlock(const EBlockLocation eBlockLocation) const
{
    m_sprite->render(m_position + m_blockOffsets[static_cast<size_t>(eBlockLocation)], m_size / 2.f, m_fRotation, m_fLayer);
}

void CTrees::render() const
{
    renderBlock(EBlockLocation::TopLeft);
    renderBlock(EBlockLocation::TopRight);
    renderBlock(EBlockLocation::BottomLeft);
    renderBlock(EBlockLocation::BottomRight);
}