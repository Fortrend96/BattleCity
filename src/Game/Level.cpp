#include "Level.h"
#include "GameObjects/BrickWall.h"
#include "../Resources/ResourceManager.h"

#include <iostream>

const unsigned int BLOCK_SIZE = 16;

std::shared_ptr<IGameObject> createGameObjectFromDescription(const char description,
	const glm::vec2& position, const glm::vec2& size, const float fRotation)
{
	switch (description)
	{
	case '0':
		return std::make_shared<CBrickWall>(CResourceManager::getSprite("brickWall_right"), position, size, fRotation);
	case '1':
		return std::make_shared<CBrickWall>(CResourceManager::getSprite("brickWall_bottom"), position, size, fRotation);
	case '2':
		return std::make_shared<CBrickWall>(CResourceManager::getSprite("brickWall_left"), position, size, fRotation);
	case '3':
		return std::make_shared<CBrickWall>(CResourceManager::getSprite("brickWall_top"), position, size, fRotation);
	case '4':
		return std::make_shared<CBrickWall>(CResourceManager::getSprite("brickWall"), position, size, fRotation);
	case 'G':
		return std::make_shared<CBrickWall>(CResourceManager::getSprite("brickWall_bottom_left"), position, size, fRotation);
	case 'H':
		return std::make_shared<CBrickWall>(CResourceManager::getSprite("brickWall_bottom_right"), position, size, fRotation);
	case 'I':
		return std::make_shared<CBrickWall>(CResourceManager::getSprite("brickWall_top_left"), position, size, fRotation);
	case 'J':
		return std::make_shared<CBrickWall>(CResourceManager::getSprite("brickWall_top_right"), position, size, fRotation);
	case 'D':
		return nullptr;
	default:
		std::cerr << "unknown GameObject description : " << description << std::endl;
		break;
	}

	return nullptr;
}

CLevel::CLevel(const std::vector<std::string>& levelDescription)
{
	if (levelDescription.empty())
	{
		std::cerr << "Empty level description" << std::endl;
	}

	m_iWidth = levelDescription[0].length();
	m_iHeight = levelDescription.size();

	m_mapObjects.reserve(m_iWidth * m_iHeight);
	unsigned int iCurBottomOffset = static_cast<unsigned int>(BLOCK_SIZE * (m_iHeight - 1));

	for (const auto& curRow : levelDescription)
	{
		unsigned int iCurLeftOffset = 0;
		for (const char curElement : curRow)
		{
			std::shared_ptr<IGameObject> pGameObject =
				createGameObjectFromDescription(curElement, glm::vec2(iCurLeftOffset, iCurBottomOffset),
					glm::vec2(BLOCK_SIZE, BLOCK_SIZE), 0);

			m_mapObjects.emplace_back(std::move(pGameObject));

			iCurLeftOffset += BLOCK_SIZE;
		}
		iCurBottomOffset -= BLOCK_SIZE;
	}

}

void CLevel::render() const
{
	for (const auto& curMapObject : m_mapObjects)
	{
		if (curMapObject)
		{
			curMapObject->render();
		}
	}
}

void CLevel::update(const uint64_t delta)
{
	for (const auto& curMapObject : m_mapObjects)
	{
		if (curMapObject)
		{
			curMapObject->update(delta);
		}
	}
}
