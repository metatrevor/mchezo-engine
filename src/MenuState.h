#ifndef MENUSTATE_H
#define MENUSTATE_H

#include "State.h"
#include "Log.h"
#include "Object.h"
#include "StateManager.h"

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
    static void gameToMenu();
};

#endif // MENUSTATE_H
