#include "AnimatedGraphic.h"

AnimatedGraphic::AnimatedGraphic(int x, int y, int height, int width, std::string textureKeyName, int animationSpeed)
        : Object(x, y, height, width, textureKeyName), m_animationSpeed(animationSpeed)
{
    m_velocity.setY(2);
    m_velocity.setX(0.001);
}


void AnimatedGraphic::draw()
{
    TextureManager::instance().drawFrame(m_textureKeyName, (int) m_position.getX(), (int) m_position.getY(), m_width,
                                         m_height,
                                         m_currentRow, m_currentFrame);
}

void AnimatedGraphic::update()
{
    Object::update();

    m_currentFrame = int((SDL_GetTicks() / 1000 / m_animationSpeed) % 2);

    if (m_position.getY() < 0) {
        m_velocity.setY(2);
    }
    else if (m_position.getY() > 400) {
        m_velocity.setY(-2);
    }
}


void AnimatedGraphic::clean()
{

}
