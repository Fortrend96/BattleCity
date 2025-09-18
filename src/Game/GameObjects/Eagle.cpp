#include "Eagle.h"

#include "../../Resources/ResourceManager.h"
#include "../../Renderer/Sprite.h"

CEagle::CEagle(const glm::vec2& position, const glm::vec2& size, const float rotation)
    : IGameObject(position, size, rotation)
    , m_sprite{ CResourceManager::getSprite("eagle"),
                CResourceManager::getSprite("eagle_dead") }
    , m_eCurrentState(EEagleState::Alive)
{
}

void CEagle::render() const
{
    m_sprite[static_cast<size_t>(m_eCurrentState)]->render(m_position, m_size, m_fRotation);
}

void CEagle::update(const uint64_t delta)
{

}
