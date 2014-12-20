#ifndef GAMEOVERSTATE_H
#define GAMEOVERSTATE_H

#include "Object.h"
#include "State.h"
#include <vector>

class GameOverState : public State
{
public:
    GameOverState();

    bool init();
    void run();
    void render();
    void update();
    void exit();
    void handleEvents();

private:
    static void gameOverToMenu();
    static void gameOverToRestartGame();
};

#endif // GAMEOVERSTATE_H
