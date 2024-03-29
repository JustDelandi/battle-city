#include "game.h"
#include <iostream>

#include "../Renderer/shaderProgram.h"
#include "../Resources/resourceManager.h"
#include "../Renderer/texture2D.h"
#include "../Renderer/sprite.h"
#include "../Renderer//AnimatedSprite.h"

#include "GameObjects/tank.h"
#include "level.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/mat4x4.hpp>
#include <GLFW/glfw3.h>

Game::Game(const glm::ivec2& windowSize)
	:
	m_eCurrentGameState(EGameState::Active),
    m_windowSize(windowSize)
{
	m_keys.fill(false);

}

Game::~Game()
{

}

void Game::render()
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

void Game::update(const uint64_t delta)
{   
    if (m_pLevel)
    {
        m_pLevel->update(delta);
    }

    if (m_pTank)
    {
        if (m_keys[GLFW_KEY_W])
        {
            m_pTank->setOrientation(Tank::EOrientation::Top);
            m_pTank->move(true);
        }
        else if (m_keys[GLFW_KEY_A])
        {
            m_pTank->setOrientation(Tank::EOrientation::Left);
            m_pTank->move(true);
        }
        else if (m_keys[GLFW_KEY_D])
        {
            m_pTank->setOrientation(Tank::EOrientation::Right);
            m_pTank->move(true);
        }
        else if (m_keys[GLFW_KEY_S])
        {
            m_pTank->setOrientation(Tank::EOrientation::Bottom);
            m_pTank->move(true);
        }
        else
        {
            m_pTank->move(false);
        }

        m_pTank->update(delta);
    }


}

void Game::setKey(const int key, const int action)
{
	m_keys[key] = action; 
}

bool Game::init()
{
        ResourceManager::loadJSONResources("res/resources.json");

        auto pSpriteShaderProgram = ResourceManager::getShaderProgram("spriteShader");
        if (!pSpriteShaderProgram)
        {
            std::cerr << "Can't find shader program: " << "spriteShader" << std::endl;
            return false;
        }

        auto pTextureAtlas = ResourceManager::getTextures("mapTextureAtlas");
        if (!pTextureAtlas)
        {
            std::cerr << "Can't find texture atlas: " << "mapTextureAtlas" << std::endl;
            return false;
        }

        auto pTanksTextureAtlas = ResourceManager::getTextures("tanksTextureAtlas");
        if (!pTanksTextureAtlas)
        {
            std::cerr << "Can't find texture atlas: " << "tanksTextureAtlas" << std::endl;
            return false;
        }

        glm::mat4 projectionMatrix = glm::ortho(0.f, static_cast<float>(m_windowSize.x), 0.f, static_cast<float>(m_windowSize.y), -100.f, 100.f);

        pSpriteShaderProgram->use();
        pSpriteShaderProgram->setInt("tex", 0);
        pSpriteShaderProgram->setMatrix4("projectionMat", projectionMatrix);
        
        auto pTanksAnimatedSprite = ResourceManager::getAnimatedSprite("tankAnimatedSprite");
        if (!pTanksAnimatedSprite)
        {
            std::cerr << "Can't find animated sprite: " << "tankAnimatedSprite" << std::endl;
            return false;
        }

        m_pTank = std::make_unique<Tank>(pTanksAnimatedSprite, 0.0000001f, glm::vec2(0.f, 0.f), glm::vec2(16.f, 16.f));
        m_pLevel = std::make_unique<Level>(ResourceManager::getLevels()[0]);
        return true;
}