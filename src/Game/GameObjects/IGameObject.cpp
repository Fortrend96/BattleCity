#include "IGameObject.h"

IGameObject::IGameObject(const EObjectType objectType, const glm::vec2& position, const glm::vec2& size, const float fRotation, const float fLayer):
						m_position(position)
						, m_size(size)
						, m_rotation(fRotation)
						, m_layer(fLayer)
						, m_objectType(objectType)
						, m_direction(0, 1.f)
						, m_velocity(0)
{

}

IGameObject::~IGameObject()
{

}

void IGameObject::setVelocity(const double dVelocity)
{
	m_velocity = dVelocity;
}
