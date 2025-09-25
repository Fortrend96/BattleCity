#include "Level.h"
#include "GameObjects/BrickWall.h"
#include "GameObjects/BetonWall.h"
#include "GameObjects/Water.h"
#include "GameObjects/Trees.h"
#include "GameObjects/Ice.h"
#include "GameObjects/Eagle.h"
#include "GameObjects/Border.h"
#include <iostream>
#include <algorithm>
#include <cmath>



std::unique_ptr<IGameObject> createGameObjectFromDescription(const char description,
	const glm::vec2& position, const glm::vec2& size, const float fRotation)
{
	switch (description)
	{
	case '0':
		return std::make_unique<CBrickWall>(CBrickWall::EBrickWallType::Right, position, size, fRotation, 0.f);
	case '1':
		return std::make_unique<CBrickWall>(CBrickWall::EBrickWallType::Bottom, position, size, fRotation, 0.f);
	case '2':
		return std::make_unique<CBrickWall>(CBrickWall::EBrickWallType::Left, position, size, fRotation, 0.f);
	case '3':
		return std::make_unique<CBrickWall>(CBrickWall::EBrickWallType::Top, position, size, fRotation, 0.f);
	case '4':
		return std::make_unique<CBrickWall>(CBrickWall::EBrickWallType::All, position, size, fRotation, 0.f);
	case 'G':
		return std::make_unique<CBrickWall>(CBrickWall::EBrickWallType::BottomLeft, position, size, fRotation, 0.f);
	case 'H':
		return std::make_unique<CBrickWall>(CBrickWall::EBrickWallType::BottomRight, position, size, fRotation, 0.f);
	case 'I':
		return std::make_unique<CBrickWall>(CBrickWall::EBrickWallType::TopLeft, position, size, fRotation, 0.f);
	case 'J':
		return std::make_unique<CBrickWall>(CBrickWall::EBrickWallType::TopRight, position, size, fRotation, 0.f);
	case '5':
		return std::make_unique<CBetonWall>(CBetonWall::EBetonWallType::Right, position, size, fRotation, 0.f);
	case '6':
		return std::make_unique<CBetonWall>(CBetonWall::EBetonWallType::Bottom, position, size, fRotation, 0.f);
	case '7':
		return std::make_unique<CBetonWall>(CBetonWall::EBetonWallType::Left, position, size, fRotation, 0.f);
	case '8':
		return std::make_unique<CBetonWall>(CBetonWall::EBetonWallType::Top, position, size, fRotation, 0.f);
	case '9':
		return std::make_unique<CBetonWall>(CBetonWall::EBetonWallType::All, position, size, fRotation, 0.f);
	case 'A':
		return std::make_unique<CWater>(position, size, fRotation, 0.f);
	case 'B':
		return std::make_unique<CTrees>(position, size, fRotation, 1.f);
	case 'C':
		return std::make_unique<CIce>(position, size, fRotation, -1.f);
	case 'E':
		return std::make_unique<CEagle>(position, size, fRotation, 0.f);
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

	m_iWidthBlocks = levelDescription[0].length();
	m_iHeightBlocks = levelDescription.size();

	m_iWidthPixels = static_cast<unsigned int>(m_iWidthBlocks * BLOCK_SIZE);
	m_iHeightPixels = static_cast<unsigned int>(m_iHeightBlocks * BLOCK_SIZE);

	m_playerRespawn_1 = { BLOCK_SIZE * (m_iWidthBlocks / 2 - 1),	BLOCK_SIZE / 2 };
	m_playerRespawn_2 = { BLOCK_SIZE * (m_iWidthBlocks / 2 + 3),	BLOCK_SIZE / 2 };
	m_enemyRespawn_1 =	{ BLOCK_SIZE,								BLOCK_SIZE *  m_iHeightBlocks - BLOCK_SIZE / 2 };
	m_enemyRespawn_2 =	{ BLOCK_SIZE * (m_iWidthBlocks / 2 + 1),			BLOCK_SIZE * m_iHeightBlocks - BLOCK_SIZE / 2 };
	m_enemyRespawn_3 =	{ BLOCK_SIZE * m_iWidthBlocks,					BLOCK_SIZE * m_iHeightBlocks - BLOCK_SIZE / 2 };

	m_levelObjects.reserve(m_iWidthBlocks * m_iHeightBlocks + 4);
	unsigned int iCurBottomOffset = static_cast<unsigned int>(BLOCK_SIZE * (m_iHeightBlocks - 1) + BLOCK_SIZE / 2.f);

	for (const auto& curRow : levelDescription)
	{
		unsigned int iCurLeftOffset = BLOCK_SIZE;
		for (const char curElement : curRow)
		{
			switch (curElement)
			{
			case 'K':
				m_playerRespawn_1 = { iCurLeftOffset, iCurBottomOffset };
				m_levelObjects.emplace_back(nullptr);
				break;
			case 'L':
				m_playerRespawn_2 = { iCurLeftOffset, iCurBottomOffset };
				m_levelObjects.emplace_back(nullptr);
				break;
			case 'M':
				m_enemyRespawn_1 = { iCurLeftOffset, iCurBottomOffset };
				m_levelObjects.emplace_back(nullptr);
				break;
			case 'N':
				m_enemyRespawn_2 = { iCurLeftOffset, iCurBottomOffset };
				m_levelObjects.emplace_back(nullptr);
				break;
			case 'O':
				m_enemyRespawn_3 = { iCurLeftOffset, iCurBottomOffset };
				m_levelObjects.emplace_back(nullptr);
				break;
			default:
				m_levelObjects.emplace_back(createGameObjectFromDescription(curElement, glm::vec2(iCurLeftOffset, iCurBottomOffset), glm::vec2(BLOCK_SIZE, BLOCK_SIZE), 0.f));
				break;
			}

			iCurLeftOffset += BLOCK_SIZE;
		}
		iCurBottomOffset -= BLOCK_SIZE;
	}

	// bottom border
	m_levelObjects.emplace_back(std::make_unique<CBorder>(glm::vec2(BLOCK_SIZE, 0.f), 
		glm::vec2(m_iWidthBlocks * BLOCK_SIZE, BLOCK_SIZE / 2.f), 0.f, 0.f));

	// top border
	m_levelObjects.emplace_back(std::make_unique<CBorder>(glm::vec2(BLOCK_SIZE, 
		m_iHeightBlocks * BLOCK_SIZE + BLOCK_SIZE / 2.f), glm::vec2(m_iWidthBlocks * BLOCK_SIZE, BLOCK_SIZE / 2.f), 0.f, 0.f));

	// left border
	m_levelObjects.emplace_back(std::make_unique<CBorder>(glm::vec2(0.f, 0.f), 
		glm::vec2(BLOCK_SIZE, (m_iHeightBlocks + 1) * BLOCK_SIZE), 0.f, 0.f));

	// right border
	m_levelObjects.emplace_back(std::make_unique<CBorder>(glm::vec2((m_iWidthBlocks + 1) * BLOCK_SIZE, 0.f), 
		glm::vec2(BLOCK_SIZE * 2.f, (m_iHeightBlocks + 1) * BLOCK_SIZE), 0.f, 0.f));

}

void CLevel::render() const
{
	for (const auto& curLevelObject : m_levelObjects)
	{
		if (curLevelObject)
		{
			curLevelObject->render();
		}
	}
}

void CLevel::update(const double delta)
{
	for (const auto& curLevelObject : m_levelObjects)
	{
		if (curLevelObject)
		{
			curLevelObject->update(delta);
		}
	}
}

size_t CLevel::getLevelWidth() const
{
	return (m_iWidthBlocks + 3) * BLOCK_SIZE;
}

size_t CLevel::getLevelHeight() const
{
	return (m_iHeightBlocks + 1) * BLOCK_SIZE;
}

std::vector<std::shared_ptr<IGameObject>> CLevel::getObjectsInArea(const glm::vec2& bottomLeft, const glm::vec2& topRight)
{
	std::vector<std::shared_ptr<IGameObject>> output;
	output.reserve(9);

	glm::vec2 bottomLeft_converted(std::clamp(bottomLeft.x - BLOCK_SIZE, 0.f, static_cast<float>(m_iWidthPixels)),
		std::clamp(m_iHeightPixels - bottomLeft.y + BLOCK_SIZE / 2, 0.f, static_cast<float>(m_iHeightPixels)));
	glm::vec2 topRight_converted(std::clamp(topRight.x - BLOCK_SIZE, 0.f, static_cast<float>(m_iWidthPixels)),
		std::clamp(m_iHeightPixels - topRight.y + BLOCK_SIZE / 2, 0.f, static_cast<float>(m_iHeightPixels)));

	size_t startX = static_cast<size_t>(floor(bottomLeft_converted.x / BLOCK_SIZE));
	size_t endX = static_cast<size_t>(ceil(topRight_converted.x / BLOCK_SIZE));

	size_t startY = static_cast<size_t>(floor(topRight_converted.y / BLOCK_SIZE));
	size_t endY = static_cast<size_t>(ceil(bottomLeft_converted.y / BLOCK_SIZE));

	for (size_t currentColumn = startX; currentColumn < endX; ++currentColumn)
	{
		for (size_t currentRow = startY; currentRow < endY; ++currentRow)
		{
			auto& currentObject = m_levelObjects[currentRow * m_iWidthBlocks + currentColumn];
			if (currentObject)
			{
				output.push_back(currentObject);
			}
		}
	}

	if (endX >= m_iWidthBlocks)
	{
		output.push_back(m_levelObjects[m_levelObjects.size() - 1]);
	}
	if (startX <= 1)
	{
		output.push_back(m_levelObjects[m_levelObjects.size() - 2]);
	}
	if (startY <= 1)
	{
		output.push_back(m_levelObjects[m_levelObjects.size() - 3]);
	}
	if (endY >= m_iHeightBlocks)
	{
		output.push_back(m_levelObjects[m_levelObjects.size() - 4]);
	}

	return output;
}
