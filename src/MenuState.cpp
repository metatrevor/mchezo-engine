#include "MenuState.h"
#include "MenuButton.h"
#include "Game.h"

MenuState::MenuState()
{
}

bool MenuState::init()
{
    m_stateName = "MENU";
    Log::Info("Entering Menustate...");
    TextureManager::instance().loadTexture("play", "assets/textures/button.png");
    TextureManager::instance().loadTexture("exit", "assets/textures/exit.png");
    m_objects.push_back(new MenuButton(100, 100, 400, 100, "play", menuToGame));
    m_objects.push_back(new MenuButton(100, 300, 400, 100, "exit", menuToQuit));
    return true;
}

void MenuState::run()
{
    State::run();
}

void MenuState::render()
{
    State::render();
}

void MenuState::update()
{
    State::update();
}

void MenuState::exit()
{
    TextureManager::instance().deleteTexture("play");
    TextureManager::instance().deleteTexture("exit");
    Log::Info("Exiting Menustate...");
}

void MenuState::handleEvents()
{
    State::handleEvents();
}

void MenuState::menuToGame()
{
    Log::Info("Menu to Game clicked");
    StateManager::instance().push(new Game());
}

void MenuState::menuToQuit()
{
    Log::Info("Menu to Quit clicked");
    StateManager::instance().pop();
    StateManager::instance().quitGame();
}
