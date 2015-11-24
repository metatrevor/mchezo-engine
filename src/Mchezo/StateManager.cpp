#include "StateManager.h"

StateManager &StateManager::instance()
{
    static StateManager m_instance;
    return m_instance;
}

StateManager::StateManager()
{ }

StateManager::~StateManager()
{ }

bool StateManager::init()
{
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        Log::Error("Unable to initialize SDL" + Log::GetSDLError());
        return false;
    }
    TextureManager::instance().init();
    m_fsm_status = true;
    return true;
}

void StateManager::run(int argc, char **argv, State *initialState)
{
    if (!init()) {
        Log::Error("Init failure " + Log::GetSDLError());
        exit(EXIT_FAILURE);
    }

    else {
        instance().push(initialState);
    }

    if (m_fsm_status) {

        for(;;) {

            frameStart = SDL_GetTicks();
            m_states.back()->handleEvents();
            if(!m_fsm_status) {
                break;
            }
            m_states.back()->update();
            m_states.back()->render();

            frameTime = SDL_GetTicks() - frameStart;

            if (frameTime < FRAMEDELTA) {
                SDL_Delay((Uint32) (FRAMEDELTA - frameTime));
            }

        }
    }
}

void StateManager::push(State *state)
{
    m_states.push_back(state);
    m_states.back()->init();
    m_states.back()->run();
}

void StateManager::change(State *state)
{
    if (!m_states.empty()) {
        if (m_states.back()->getStateName() == state->getStateName())
            return;
        else {
            m_states.back()->exit();
            delete m_states.back();
            m_states.pop_back();
        }
    }
    m_states.push_back(state);
    m_states.back()->init();
    m_states.back()->run();
}

void StateManager::pop()
{
    if (!m_states.empty()) {
        Log::Info("Popping..." + m_states.back()->m_stateName);
        m_states.back()->exit();
        delete m_states.back();
        m_states.pop_back();
    }
}

void StateManager::quitGame()
{
    m_fsm_status = false;
    if(!m_states.empty()) {
        for(std::vector<State *>::iterator it = m_states.begin(); it != m_states.end(); ++it){
            (*it)->exit();
            delete (*it);
        }
    }
}
