#ifndef STATEMANAGER_H
#define STATEMANAGER_H

#include <SDL2/SDL.h>
#include <vector>
#include "State.h"
#include "Defines.h"

class StateMachine
{
public:
    static StateMachine &instance();
    bool init();
    void run(int argc, char **argv);
    void push(State *state);
    void change(State *state);
    void pop();

    void quitGame();

private:
    std::vector <State*> m_states;
    StateMachine();
    ~StateMachine();
    State* m_currentState;
    Uint32 frameStart;
    Uint32 frameTime;
    bool m_init_status;
    bool m_fsm_status;
};

#endif // STATEMANAGER_H
