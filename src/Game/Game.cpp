#include "Game.h"
#include "../Resources/ResourceManager.h"
#include "../Renderer/ShaderProgram.h"
#include "../Renderer/Texture2D.h"
#include "../Renderer/Sprite.h"

#include "GameObjects/Tank.h"
#include "Level.h"


#include <GLFW/glfw3.h>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/mat4x4.hpp>

#include <iostream>

CGame::CGame(const glm::ivec2& windowSize) :
    m_windowSize(windowSize),
	m_eCurrentGameState(EGameState::Active)
{
	m_keys.fill(false);
}

CGame::~CGame()
{

}

void CGame::render()
{
    if (m_pTank)
    {
        m_pTank->render();
    }

    if (m_pLevel)
    {
        m_pLevel->render();
    }

}

void CGame::update(const uint64_t delta)
{
    if (m_pLevel)
    {
        m_pLevel->update(delta);
    }

    if (m_pTank)
    {
        if (m_keys[GLFW_KEY_W])
        {
            m_pTank->setOrientaion(CTank::EOrientation::Top);
            m_pTank->move(true);
        }
        else if (m_keys[GLFW_KEY_A])
        {
            m_pTank->setOrientaion(CTank::EOrientation::Left);
            m_pTank->move(true);
        }
        else if (m_keys[GLFW_KEY_D])
        {
            m_pTank->setOrientaion(CTank::EOrientation::Right);
            m_pTank->move(true);
        }
        else if (m_keys[GLFW_KEY_S])
        {
            m_pTank->setOrientaion(CTank::EOrientation::Bottom);
            m_pTank->move(true);
        }
        else
        {
            m_pTank->move(false);
        }
        m_pTank->update(delta);
    }
}

void CGame::setKey(const int key, const int action)
{
	m_keys[key] = action;
}

bool CGame::init()
{
    CResourceManager::loadJSONResources("res/resources.json");

    auto pSpriteShaderProgram = CResourceManager::getShaderProgram("spriteShader");
    if (!pSpriteShaderProgram)
    {
        std::cerr << "Cant find shader program: " << "spriteShader" << std::endl;
        return false;
    }

    m_pLevel = std::make_unique<CLevel>(CResourceManager::getLevels()[0]);
    m_windowSize.x = static_cast<int>(m_pLevel->getLevelWidth());
    m_windowSize.y = static_cast<int>(m_pLevel->getLevelHeight());

    glm::mat4 projectionMatrix = glm::ortho(0.f, static_cast<float>(m_windowSize.x), 0.f, static_cast<float>(m_windowSize.y), -100.f, 100.f);

    pSpriteShaderProgram->use();
    pSpriteShaderProgram->setInt("tex", 0);
    pSpriteShaderProgram->setMatrix4("projectionMat", projectionMatrix);

    m_pTank = std::make_unique<CTank>(0.0000001f, m_pLevel->getPlayerRespawn_1(), glm::vec2(CLevel::BLOCK_SIZE,CLevel::BLOCK_SIZE), 0.f);
    return true;
}

size_t CGame::getCurrentLevelWidth() const
{
    return m_pLevel->getLevelWidth();
}

size_t CGame::getCurrentLevelHeight() const
{
    return m_pLevel->getLevelHeight();
}