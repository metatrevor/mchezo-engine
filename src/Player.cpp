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
    m_currentFrame = int(((SDL_GetTicks() / 100 ) % 6));

//    Vector2D *vec = InputManager::instance().getMousePosition();

//    m_velocity = (*vec - m_position) / 100;


    if(InputManager::instance().isKeyDown(SDL_SCANCODE_RIGHT))
        m_velocity.setX(2);
    if(InputManager::instance().isKeyDown(SDL_SCANCODE_LEFT))
        m_velocity.setX(-2);

    Object::update();
}


void Player::clean()
{

}
