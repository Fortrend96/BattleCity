#include "Level.h"
#include "GameObjects/BrickWall.h"
#include "GameObjects/BetonWall.h"
#include "GameObjects/Water.h"
#include "GameObjects/Trees.h"
#include "GameObjects/Ice.h"
#include "GameObjects/Eagle.h"
#include <iostream>

const unsigned int BLOCK_SIZE = 16;

std::shared_ptr<IGameObject> createGameObjectFromDescription(const char description,
	const glm::vec2& position, const glm::vec2& size, const float fRotation)
{
	switch (description)
	{
	case '0':
		return std::make_shared<CBrickWall>(CBrickWall::EBrickWallType::Right, position, size, fRotation, 0.f);
	case '1':
		return std::make_shared<CBrickWall>(CBrickWall::EBrickWallType::Bottom, position, size, fRotation, 0.f);
	case '2':
		return std::make_shared<CBrickWall>(CBrickWall::EBrickWallType::Left, position, size, fRotation, 0.f);
	case '3':
		return std::make_shared<CBrickWall>(CBrickWall::EBrickWallType::Top, position, size, fRotation, 0.f);
	case '4':
		return std::make_shared<CBrickWall>(CBrickWall::EBrickWallType::All, position, size, fRotation, 0.f);
	case 'G':
		return std::make_shared<CBrickWall>(CBrickWall::EBrickWallType::BottomLeft, position, size, fRotation, 0.f);
	case 'H':
		return std::make_shared<CBrickWall>(CBrickWall::EBrickWallType::BottomRight, position, size, fRotation, 0.f);
	case 'I':
		return std::make_shared<CBrickWall>(CBrickWall::EBrickWallType::TopLeft, position, size, fRotation, 0.f);
	case 'J':
		return std::make_shared<CBrickWall>(CBrickWall::EBrickWallType::TopRight, position, size, fRotation, 0.f);
	case '5':
		return std::make_shared<CBetonWall>(CBetonWall::EBetonWallType::Right, position, size, fRotation, 0.f);
	case '6':
		return std::make_shared<CBetonWall>(CBetonWall::EBetonWallType::Bottom, position, size, fRotation, 0.f);
	case '7':
		return std::make_shared<CBetonWall>(CBetonWall::EBetonWallType::Left, position, size, fRotation, 0.f);
	case '8':
		return std::make_shared<CBetonWall>(CBetonWall::EBetonWallType::Top, position, size, fRotation, 0.f);
	case '9':
		return std::make_shared<CBetonWall>(CBetonWall::EBetonWallType::All, position, size, fRotation, 0.f);
	case 'A':
		return std::make_shared<CWater>(position, size, fRotation, 0.f);
	case 'B':
		return std::make_shared<CTrees>(position, size, fRotation, 1.f);
	case 'C':
		return std::make_shared<CIce>(position, size, fRotation, -1.f);
	case 'E':
		return std::make_shared<CEagle>(position, size, fRotation, 0.f);
	case 'D':
		return nullptr;
	default:
		std::cerr << "Unknown GameObject description: " << description << std::endl;
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
