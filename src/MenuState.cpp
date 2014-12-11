#include "MenuState.h"
#include "MenuButton.h"
#include "Game.h"

MenuState::MenuState()
{
}

bool MenuState::init()
{
    m_stateName = "MENU";
    Log::Info("Entering Menustate...\n");
    TextureManager::instance().loadTexture("play", "assets/textures/button.png");
    TextureManager::instance().loadTexture("exit", "assets/textures/exit.png");
    m_objects.push_back(new MenuButton(100, 100, 400, 100, "play", menuToGame));
    m_objects.push_back(new MenuButton(100, 300, 400, 100, "exit", gameToMenu));
    return true;
}

void MenuState::run()
{
    handleEvents();
    update();
    render();
}

void MenuState::render()
{
    TextureManager::instance().getWindow()->clearRenderer();
    std::vector<Object*>::size_type i;
    for(i = 0; i < m_objects.size(); i++)
    {
    m_objects[i]->draw();
    }
    TextureManager::instance().getWindow()->updateWindow();
}

void MenuState::update()
{
    std::vector<Object*>::size_type i;
    for(i = 0; i < m_objects.size(); i++)
    {
    m_objects[i]->update();
    }

}

void MenuState::exit()
{
    std::vector<Object*>::size_type i;
    for(i = 0; i < m_objects.size(); i++)
    {
        m_objects[i]->clean();
    }
    m_objects.clear();
    TextureManager::instance().deleteTexture("play");
    TextureManager::instance().deleteTexture("exit");
    Log::Info("Exiting Menustate...\n");
}

void MenuState::handleEvents()
{
    InputManager::instance().update();
    if(InputManager::instance().onQuit())
        StateMachine::instance().quitGame();
}

void MenuState::menuToGame()
{
    Log::Info("Menu to Game clicked");
    StateMachine::instance().pop();
    StateMachine::instance().push(new Game());
}

void MenuState::gameToMenu()
{
    StateMachine::instance().quitGame();
}
