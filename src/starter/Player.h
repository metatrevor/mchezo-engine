#ifndef PLAYER_H
#define PLAYER_H

#include "../Mchezo/Object.h"
#include "../Mchezo/InputManager.h"

enum
{
    PLAYER_NONE,
    PLAYER_ONE = 1,
    PLAYER_TWO,
    PLAYER_DRAW
};

class Player : public Object
{
public:
    Player(int x, int y, int height, int width, std::string textureKeyName);

    void draw();

    void update();

    void clean();

protected:
private:
};

#endif // PLAYER_H
