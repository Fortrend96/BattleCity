#include "IGameObject.h"

IGameObject::IGameObject(const glm::vec2& position, const glm::vec2& size, const float fRotation, const float fLayer):
						m_position(position),
						m_size(size),
						m_fRotation(fRotation),
						m_fLayer(fLayer)
{

}

IGameObject::~IGameObject()
{

}
