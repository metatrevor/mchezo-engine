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
