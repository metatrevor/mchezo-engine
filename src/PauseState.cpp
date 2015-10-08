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
    std::vector<Object *>::size_type i;
    for (i = 0; i < m_objects.size(); i++) {
        m_objects[i]->draw();
    }
    TextureManager::instance().getWindow()->updateWindow();
}

void PauseState::update()
{
    std::vector<Object *>::size_type i;
    for (i = 0; i < m_objects.size(); i++) {
        m_objects[i]->update();
    }
}

void PauseState::exit()
{
    State::exit();
    Log::Info("Exiting Pausestate...\n");
}

void PauseState::handleEvents()
{
    State::handleEvents();
}

void PauseState::pauseToGame()
{
    Log::Info("Pause to Game clicked");
    StateManager::instance().pop();
    Log::Info("Resuming Game state");
}

void PauseState::pauseToMenu()
{
    Log::Info("Pause to Menu clicked");
    StateManager::instance().push(new MenuState());
}
