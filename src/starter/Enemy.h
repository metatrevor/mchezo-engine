#ifndef ENEMY_H
#define ENEMY_H

#include "../Mchezo/Object.h"

class Enemy : public Object
{
public:
    Enemy(int x, int y, int height, int width, std::string textureKeyName);

    void draw();

    void update();

    void clean();

protected:
private:
    Vector2D *m_mousePosition;
};

#endif // ENEMY_H
