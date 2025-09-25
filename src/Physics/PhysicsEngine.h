#pragma once

#include <unordered_set>
#include <memory>

#include <glm/vec2.hpp>

class IGameObject;
class CLevel;

namespace Physics
{
	struct CAxisAlignedBoundingBox
	{
		CAxisAlignedBoundingBox(const glm::vec2& _bottomLeft, 
			const glm::vec2& _topRight) :
			bottomLeft(_bottomLeft),
			topRight(_topRight)
		{}

		glm::vec2 bottomLeft;
		glm::vec2 topRight;
	};

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
		static void addDynamicGameObject(std::shared_ptr<IGameObject> pGameObject);
		static void setCurrentLevel(std::shared_ptr<CLevel> pLevel);

	private:
		static std::unordered_set<std::shared_ptr<IGameObject>> m_dynamicObjects;
		static std::shared_ptr<CLevel> m_pCurrentLevel;

		static bool hasIntersection(const std::vector<CAxisAlignedBoundingBox>& colliders1, const glm::vec2& position1,
			const std::vector<CAxisAlignedBoundingBox>& colliders2, const glm::vec2& position2);

	};
}


