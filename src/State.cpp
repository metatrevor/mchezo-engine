#include "State.h"
#include "StateManager.h"


void State::run()
{
    handleEvents();
    update();
    render();
}

void State::render()
{
    TextureManager::instance().getWindow()->clearRenderer();
    std::vector<Object *>::size_type i;
    for (i = 0; i < m_objects.size(); i++) {
        m_objects[i]->draw();
    }
    TextureManager::instance().getWindow()->updateWindow();

}

void State::update()
{
    std::vector<Object*>::size_type i;
    for (i = 0; i < m_objects.size(); i++) {
        m_objects[i]->update();
    }
}

void State::handleEvents()
{
    InputManager::instance().update();
    if (InputManager::instance().onQuit())
        StateMachine::instance().quitGame();
}