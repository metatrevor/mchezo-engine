#include "Enemy.h"

Enemy::Enemy(int x, int y, int height, int width, std::string textureKeyName)
    : Object(x, y, height, width, textureKeyName)
{
    m_velocity.setY(2);
    m_velocity.setX(0.001);
}


void Enemy::draw()
{
    Object::draw();
}

void Enemy::update()
{
    m_currentFrame = int((SDL_GetTicks()/100) % 5);

    if(m_position.getY() < 0)
    {
        m_velocity.setY(2);
    }
    else if(m_position.getY() > 400)
    {
        m_velocity.setY(-2);
    }
    Object::update();
}


void Enemy::clean()
{

}
