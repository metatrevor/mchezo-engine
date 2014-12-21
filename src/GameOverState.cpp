#include "GameOverState.h"
#include "MenuButton.h"
#include "StateManager.h"
#include "Game.h"
#include "AnimatedGraphic.h"

GameOverState::GameOverState()
{
}

bool GameOverState::init()
{
    m_stateName = "GAMEOVER";
    Log::Info("Entering GameOverState...");
    TextureManager::instance().loadTexture("gameovertext", "assets/textures/gameover.png");
    TextureManager::instance().loadTexture("restart", "assets/textures/restart.png");
    TextureManager::instance().loadTexture("main_menu", "assets/textures/main_menu.png");
    m_objects.push_back(new AnimatedGraphic(200, 100, 190, 30, "gameovertext", 2));
    m_objects.push_back(new MenuButton(200, 200, 200, 80, "main_menu", gameOverToMenu));
    m_objects.push_back(new MenuButton(200, 300, 200, 80, "restart", gameOverToRestartGame));
    return true;
}

void GameOverState::run()
{
    handleEvents();
    update();
    render();
}

void GameOverState::render()
{
    TextureManager::instance().getWindow()->clearRenderer();
    std::vector<Object*>::size_type i;
    for(i = 0; i < m_objects.size(); i++)
    {
        m_objects[i]->draw();
    }
    TextureManager::instance().getWindow()->updateWindow();
}

void GameOverState::update()
{
    std::vector<Object*>::size_type i;
    for(i = 0; i < m_objects.size(); i++)
    {
        m_objects[i]->update();
    }
}

void GameOverState::exit()
{
    State::exit();
    TextureManager::instance().deleteTexture("main_menu");
    TextureManager::instance().deleteTexture("restart");
    TextureManager::instance().deleteTexture("gameover");
    Log::Info("Exiting GameOverState...\n");
}

void GameOverState::handleEvents()
{
    State::handleEvents();
}

void GameOverState::gameOverToMenu()
{
    Log::Info("Game over to Menu clicked");
}

void GameOverState::gameOverToRestartGame()
{
    Log::Info("GameOver to Restart Game clicked");
    StateMachine::instance().push(new Game());
}
