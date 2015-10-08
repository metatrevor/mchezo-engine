#ifndef GAME_H
#define GAME_H

#include "TextureManager.h"
#include "Window.h"

#include "Object.h"
#include "Player.h"
#include "Enemy.h"
#include "State.h"
#include "InputManager.h"
#include "Level.h"

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
