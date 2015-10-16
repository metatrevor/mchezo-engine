#ifndef STATEMANAGER_H
#define STATEMANAGER_H

#include <SDL2/SDL.h>
#include <vector>
#include "State.h"
#include "Defines.h"

class StateManager
{
public:
    static StateManager &instance();

    bool init();

    void run(int argc, char **argv, State *initialState);

    void push(State *state);

    void change(State *state);

    void pop();

    void quitGame();

private:
    std::vector<State *> m_states;

    StateManager();

    ~StateManager();

    State *m_currentState;
    Uint32 frameStart;
    Uint32 frameTime;
    bool m_fsm_status;
};

#endif // STATEMANAGER_H
