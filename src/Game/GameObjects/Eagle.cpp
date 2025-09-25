#include "Eagle.h"

#include "../../Resources/ResourceManager.h"
#include "../../Renderer/Sprite.h"

CEagle::CEagle(const glm::vec2& position, const glm::vec2& size, const float rotation, const float fLayer)
    : IGameObject(IGameObject::EObjectType::Eagle, position, size, rotation, fLayer)
    , m_sprite{ CResourceManager::getSprite("eagle"),
                CResourceManager::getSprite("eagle_dead") }
    , m_eCurrentState(EEagleState::Alive)
{
    m_colliders.emplace_back(glm::vec2(0), m_size);
}

void CEagle::render() const
{
    m_sprite[static_cast<size_t>(m_eCurrentState)]->render(m_position, m_size, m_fRotation, m_fLayer);
}

void CEagle::update(const double delta)
{

}
