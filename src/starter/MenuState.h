#ifndef MENUSTATE_H
#define MENUSTATE_H

#include "../Mchezo/State.h"
#include "../Mchezo/Log.h"
#include "../Mchezo/Object.h"
#include "../Mchezo/StateManager.h"

class MenuState : public State
{
public:
    MenuState();

    bool init();

    void run();

    void render();

    void update();

    void exit();

    void handleEvents();

private:
    static void menuToGame();

    static void menuToQuit();
};

#endif // MENUSTATE_H
