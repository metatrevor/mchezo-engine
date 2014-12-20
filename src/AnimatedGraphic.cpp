#include "AnimatedGraphic.h"

AnimatedGraphic::AnimatedGraphic(int x, int y, int height, int width, std::string textureKeyName, int animationSpeed)
    : Object(x, y, height, width, textureKeyName), m_animationSpeed(animationSpeed)
{
    m_velocity.setY(2);
    m_velocity.setX(0.001);
}


void AnimatedGraphic::draw()
{
    Object::draw();
}

void AnimatedGraphic::update()
{
    m_currentFrame = int((SDL_GetTicks()/1000 / m_animationSpeed) % 5);

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


void AnimatedGraphic::clean()
{

}
