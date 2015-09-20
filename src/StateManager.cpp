#include "StateManager.h"
#include "MenuState.h"

StateMachine &StateMachine::instance()
{
    static StateMachine m_instance;
    return m_instance;
}

StateMachine::StateMachine()
{}

StateMachine::~StateMachine()
{}

bool StateMachine::init()
{
    if(SDL_Init(SDL_INIT_EVERYTHING) != 0)
    {
        Log::Error("Unable to initialize SDL" + Log::GetSDLError());
        return false;
    }
    TextureManager::instance().init();
    instance().change(new MenuState());
    m_fsm_status= true;
    return true;
}

void StateMachine::run(int argc, char** argv)
{
    if(!init())
    {
        Log::Error("Init failure " + Log::GetSDLError());
        exit(EXIT_FAILURE);
    }

    if(m_fsm_status)
    {
        do {
                frameStart = SDL_GetTicks();
                m_states.back()->handleEvents();
                m_states.back()->update();
                m_states.back()->render();

                frameTime = SDL_GetTicks() - frameStart;

                if(frameTime < FRAMEDELTA)
                {
                    SDL_Delay((int)(FRAMEDELTA - frameTime));
                }
        }
         while (m_fsm_status);
         m_states.back()->exit();
         m_states.clear();
    }


}

void StateMachine::push(State *state)
{
    m_states.push_back(state);
    m_states.back()->init();
    m_states.back()->run();
}

void StateMachine::change(State *state)
{
    if(!m_states.empty())
    {
        if(m_states.back()->getStateName() == state->getStateName())
            return;
        else
        {
            m_states.back()->exit();
            delete m_states.back();
            m_states.pop_back();
        }
    }
    m_states.push_back(state);
    m_states.back()->init();
    m_states.back()->run();
}

void StateMachine::pop()
{
    if(!m_states.empty())
    {
        Log::Info("Popping..." + m_states.back()->m_stateName);
        m_states.back()->exit();
        delete m_states.back();
        m_states.pop_back();
    }
}

void StateMachine::quitGame()
{
    m_fsm_status = false;
}
