#include "PauseState.h"
#include "MenuButton.h"
#include "StateManager.h"
#include "MenuState.h"

PauseState::PauseState()
{
}

bool PauseState::init()
{
    m_stateName = "PAUSE";
    Log::Info("Entering Pausestate...\n");
    TextureManager::instance().loadTexture("resume", "assets/textures/resume.png");
    TextureManager::instance().loadTexture("main_menu", "assets/textures/main_menu.png");
    m_objects.push_back(new MenuButton(100, 100, 400, 100, "resume", pauseToGame));
    m_objects.push_back(new MenuButton(100, 300, 400, 100, "main_menu", pauseToMenu));
    return true;
}

void PauseState::run()
{
    handleEvents();
    update();
    render();
}

void PauseState::render()
{
    TextureManager::instance().getWindow()->clearRenderer();
    std::vector<Object*>::size_type i;
    for(i = 0; i < m_objects.size(); i++)
    {
        m_objects[i]->draw();
    }
    TextureManager::instance().getWindow()->updateWindow();
}

void PauseState::update()
{
    std::vector<Object*>::size_type i;
    for(i = 0; i < m_objects.size(); i++)
    {
        m_objects[i]->update();
    }
}

void PauseState::exit()
{
    std::vector<Object*>::size_type i;
    for(i = 0; i < m_objects.size(); i++)
    {
        m_objects[i]->clean();
    }
    m_objects.clear();
    TextureManager::instance().deleteTexture("main_menu");
    TextureManager::instance().deleteTexture("resume");
    Log::Info("Exiting Menustate...\n");
}

void PauseState::handleEvents()
{
    State::handleEvents();
}

void PauseState::pauseToGame()
{
    StateMachine::instance().pop();
}

void PauseState::pauseToMenu()
{
    StateMachine::instance().pop();
    StateMachine::instance().pop();
    StateMachine::instance().push(new MenuState());
}
