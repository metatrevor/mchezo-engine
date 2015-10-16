#include "../Mchezo/MenuButton.h"
#include "../Mchezo/StateManager.h"
#include "../Mchezo/AnimatedGraphic.h"
#include "GameOverState.h"
#include "Game.h"


GameOverState::GameOverState()
{
}

bool GameOverState::init()
{
    m_stateName = "GAMEOVER";
    Log::Info("Entering GameOverState...");
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
    std::vector<Object *>::size_type i;
    for (i = 0; i < m_objects.size(); i++) {
        m_objects[i]->draw();
    }
    TextureManager::instance().getWindow()->updateWindow();
}

void GameOverState::update()
{
    std::vector<Object *>::size_type i;
    for (i = 0; i < m_objects.size(); i++) {
        m_objects[i]->update();
    }
}

void GameOverState::exit()
{
    State::exit();
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
    StateManager::instance().push(new Game());
}
