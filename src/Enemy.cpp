#include "Enemy.h"

Enemy::Enemy(int x, int y, int height, int width, std::string textureKeyName)
    : Object(x, y, height, width, textureKeyName)
{
}


void Enemy::draw()
{
    Object::draw();
}

void Enemy::update()
{

}


void Enemy::clean()
{

}
