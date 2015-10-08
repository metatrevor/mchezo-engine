#ifndef PAUSESTATE_H
#define PAUSESTATE_H

#include "Object.h"
#include "State.h"
#include <vector>

class PauseState : public State
{
public:
    PauseState();

    bool init();

    void run();

    void render();

    void update();

    void exit();

    void handleEvents();

private:
    static void pauseToGame();

    static void pauseToMenu();
};

#endif // PAUSESTATE_H
