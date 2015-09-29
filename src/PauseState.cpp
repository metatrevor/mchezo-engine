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
    m_objects.push_back(new MenuButton(200, 100, 200, 80, "resume", pauseToGame));
    m_objects.push_back(new MenuButton(200, 300, 200, 80, "main_menu", pauseToMenu));
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
    TextureManager::instance().deleteTexture("main_menu");
    TextureManager::instance().deleteTexture("resume");
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
