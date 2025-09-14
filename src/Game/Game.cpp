#include "Game.h"
#include "../Resources/ResourceManager.h"
#include "../Renderer/ShaderProgram.h"
#include "../Renderer/Texture2D.h"
#include "../Renderer/Sprite.h"
#include "../Renderer/AnimatedSprite.h"

#include "Tank.h"

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
    CResourceManager::getAnimatedSprite("NewAnimatedSprite")->render();
    if (m_pTank)
    {
        m_pTank->render();
    }
}

void CGame::update(const uint64_t delta)
{
    CResourceManager::getAnimatedSprite("NewAnimatedSprite")->update(delta);

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

    auto pTextureAtlas = CResourceManager::getTexture("mapTextureAtlas");
    if (!pTextureAtlas)
    {
        std::cerr << "Cant find texture atlas: " << "mapTextureAtlas" << std::endl;
        return false;
    }

    auto pTanksTextureAtlas = CResourceManager::getTexture("tanksTextureAtlas");

    if (!pTanksTextureAtlas)
    {
        std::cerr << "Cant find texture atlas: " << "tanksTextureAtlas" << std::endl;
        return false;
    }



    auto pAnimatedSprite = CResourceManager::loadAnimatedSprite("NewAnimatedSprite", "mapTextureAtlas", "spriteShader", 100, 100, "beton");
    pAnimatedSprite->setPosition(glm::vec2(300, 300));


    std::vector<std::pair<std::string, uint64_t>> waterState;
    waterState.emplace_back(std::make_pair<std::string, uint64_t>("water1", 1000000000));
    waterState.emplace_back(std::make_pair<std::string, uint64_t>("water2", 1000000000));
    waterState.emplace_back(std::make_pair<std::string, uint64_t>("water3", 1000000000));

    std::vector<std::pair<std::string, uint64_t>> eagleState;
    eagleState.emplace_back(std::make_pair<std::string, uint64_t>("eagle", 1000000000));
    eagleState.emplace_back(std::make_pair<std::string, uint64_t>("deadEagle", 1000000000));

    pAnimatedSprite->insertState("waterState", std::move(waterState));
    pAnimatedSprite->insertState("eagleState", std::move(eagleState));

    pAnimatedSprite->setState("waterState");



    glm::mat4 projectionMatrix = glm::ortho(0.f, static_cast<float>(m_windowSize.x), 0.f, static_cast<float>(m_windowSize.y), -100.f, 100.f);

    pSpriteShaderProgram->use();
    pSpriteShaderProgram->setInt("tex", 0);
    pSpriteShaderProgram->setMatrix4("projectionMat", projectionMatrix);



    auto pTanksAnimatedSprite = CResourceManager::getAnimatedSprite("tankAnimatedSprite");
    if (!pTanksAnimatedSprite)
    {
        std::cerr << "Can't find animated sprite: " << "tankAnimatedSprite" << std::endl;
        return false;
    }

    m_pTank = std::make_unique<CTank>(pTanksAnimatedSprite, 0.0000001f, glm::vec2(100.f, 100.f));
    return true;
}