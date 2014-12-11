#ifndef GAME_H
#define GAME_H

#include "TextureManager.h"
#include "Window.h"

#include "Object.h"
#include "Player.h"
#include "Enemy.h"
#include "State.h"
#include "InputManager.h"

#include <vector>

class Game : public State
{
    public:
        Game();
        ~Game(){}

    bool init();
    void run();
    void render();
    void update();
    void exit();
    void handleEvents();

    private:
        std::vector <Object *> m_objects;
};

#endif // ENGINE_H
