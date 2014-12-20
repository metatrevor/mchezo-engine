#include "Game.h"
#include "MenuState.h"
#include "PauseState.h"
#include "Enemy.h"

Game::Game()
{
}

bool Game::init()
{
    TextureManager::instance().loadTexture("animate", "assets/textures/player.png");
    TextureManager::instance().loadTexture("enemy", "assets/textures/enemy.png");
    m_objects.push_back(new Player(500, 100, 128, 55, "animate"));
    m_objects.push_back(new Enemy(100, 100, 128, 55, "enemy"));
    m_stateName = "GAME";
    Log::Info("Entering Gamestate...");
    return true;
}

void Game::run()
{
    State::run();
}

void Game::handleEvents()
{
    State::handleEvents();
   if(InputManager::instance().isKeyDown(SDL_SCANCODE_ESCAPE)) {
       gameToPause();
   }

}

void Game::render()
{
    State::render();
}

void Game::update()
{
    State::update();
}

void Game::exit()
{
 Log::Info("Exiting Gamestate...");
}

void Game::gameToPause()
{
    StateMachine::instance().push(new PauseState());
}
