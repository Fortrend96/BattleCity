#include "PhysicsEngine.h"

#include "../Game/GameObjects/IGameObject.h"

std::unordered_set<std::shared_ptr<IGameObject>> CPhysicsEngine::m_dynamicObjects;

void CPhysicsEngine::init()
{

}

void CPhysicsEngine::terminate()
{
	m_dynamicObjects.clear();
}

void CPhysicsEngine::update(const double delta)
{
	for (auto& currentObject : m_dynamicObjects)
	{
		if (currentObject->getCurrentVelocity() > 0)
		{
			currentObject->getCurrentPosition() += currentObject->getCurrentDirection() * 
				static_cast<float>(currentObject->getCurrentVelocity() * delta);
		}		
	}
}

void CPhysicsEngine::addDynamicGameObject(std::shared_ptr<IGameObject> pGameObjects)
{
	m_dynamicObjects.insert(std::move(pGameObjects));
}
