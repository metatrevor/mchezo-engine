#include "Game.h"

Game::Game()
{
}

bool Game::init()
{
    TextureManager::instance().loadTexture("animate", "assets/textures/animate.png");
    m_objects.push_back(new Player(0, 0, 128, 82, "animate"));
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
}

void Game::render()
{
    State::run();
}

void Game::update()
{
    State::update();
}

void Game::exit()
{
 Log::Info("Exiting Gamestate...");
}
