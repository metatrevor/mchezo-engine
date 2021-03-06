#include "Object.h"

Object::Object(int x, int y, int width, int height, std::string textureName)
        : m_width(width),
          m_height(height),
          m_textureKeyName(textureName),
          m_position(x, y),
          m_velocity(0, 0),
          m_acceleration(0, 0)
{
    m_currentFrame = 1;
    m_currentRow = 1;
}

void Object::draw()
{
    // TODO : Replace behaviour below with something useful

    if (m_velocity.getX() > 0)
        TextureManager::instance().drawFrame(m_textureKeyName, (int) m_position.getX(), (int) m_position.getY(),
                                             m_width, m_height,
                                             m_currentRow, m_currentFrame, SDL_FLIP_HORIZONTAL);
    else
        TextureManager::instance().drawFrame(m_textureKeyName, (int) m_position.getX(), (int) m_position.getY(),
                                             m_width, m_height,
                                             m_currentRow, m_currentFrame, SDL_FLIP_NONE);
}

void Object::update()
{
    m_velocity += m_acceleration;
    m_position += m_velocity;
}

void Object::clean()
{

}
