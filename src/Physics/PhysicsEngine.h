#pragma once

#include <unordered_set>
#include <memory>

class IGameObject;

class CPhysicsEngine 
{
public:
	CPhysicsEngine() = delete;
	~CPhysicsEngine() = delete;
	CPhysicsEngine(const CPhysicsEngine&) = delete;
	CPhysicsEngine& operator=(const CPhysicsEngine&) = delete;
	CPhysicsEngine(CPhysicsEngine&&) = delete;
	CPhysicsEngine& operator=(CPhysicsEngine&&) = delete;

	static void init();
	static void terminate();
	static void update(const double delta);
	static void addDynamicGameObject(std::shared_ptr<IGameObject> pGameObjects);

private:
	static std::unordered_set<std::shared_ptr<IGameObject>> m_dynamicObjects;

};
