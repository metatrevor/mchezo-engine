#include "Game.h"

Game::Game()
{
    m_running = false;
}

bool Game::init()
{
    TextureManager::instance().init();
    TextureManager::instance().loadTexture("animate", "assets/textures/animate.png");
    m_objects.push_back(new Player(0, 0, 128, 82, "animate"));
    m_stateName = "GAME";
    m_running = true;
    Log::Info("Entering Gamestate...");
    return true;
}

void Game::run()
{
    handleEvents();
    update();
    render();
}

void Game::handleEvents()
{
    InputManager::instance().update();
    if(InputManager::instance().onQuit())
        m_running = false;
}

void Game::render()
{
    //clear window
    TextureManager::instance().getWindow()->clearRenderer();

    std::vector<Object*>::size_type item;
    for(item = 0; item < m_objects.size(); ++item)
    {
        m_objects[item]->draw();
    }


    //draw the frame
    TextureManager::instance().getWindow()->updateWindow();

}

void Game::update()
{
    std::vector<Object*>::size_type item;
    for(item = 0; item < m_objects.size(); ++item)
    {
        m_objects[item]->update();
    }
}

void Game::exit()
{
 Log::Info("Exiting Gamestate...");
}
