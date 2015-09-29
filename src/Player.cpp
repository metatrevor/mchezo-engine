#include "Player.h"

Player::Player(int x, int y, int height, int width, std::string textureKeyName)
        : Object(x, y, height, width, textureKeyName)
{
}

void Player::draw()
{
    Object::draw();
}


void Player::update()
{
    Object::update();
}


void Player::clean()
{

}
