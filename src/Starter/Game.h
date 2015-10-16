#ifndef GAME_H
#define GAME_H

#include "../Mchezo/TextureManager.h"
#include "../Mchezo/Window.h"
#include "../Mchezo/State.h"
#include "../Mchezo/InputManager.h"
#include "../Mchezo/Level.h"
#include "../Mchezo/Object.h"
#include "Player.h"
#include "Enemy.h"

#include <vector>

class Game : public State
{
public:
    Game();

    ~Game()
    { }

    bool init();

    void run();

    void render();

    void update();

    void exit();

    void handleEvents();

    int getGameWidth() const;

    int getGameHeight() const;

    bool testCollision(Object *obj1, Object *obj2);

private:
    void gameToPause();

    int m_gameWidth;
    int m_gameHeight;
    Level *m_level;
};

#endif // ENGINE_H
