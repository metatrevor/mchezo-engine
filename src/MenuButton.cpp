#include "MenuButton.h"
#include "InputManager.h"

MenuButton::MenuButton(int x, int y, int height, int width, std::string textureKeyName, void(*callback)())
    : Object(x, y, height, width, textureKeyName), m_callback(callback)
{
    m_currentFrame = MOUSE_OUT;
}

void MenuButton::draw()
{
    Object::draw();
}

void MenuButton::update()
{
    Vector2D *mouse_pos = InputManager::instance().getMousePosition();
    if(mouse_pos->getX() < (m_position.getX() + m_width)  && mouse_pos->getX() > m_position.getX()
    && mouse_pos->getY() < (m_position.getY() + m_height) && mouse_pos->getY() > m_position.getY())
    {
        m_currentFrame = MOUSE_OVER;
        if(InputManager::instance().getMouseButtonState(LEFT) && m_released)
        {
            m_currentFrame = CLICKED;
            m_callback();
            m_released = false;
        }
        else if(!InputManager::instance().getMouseButtonState(LEFT))
        {
            m_released = true;
            m_currentFrame = CLICKED;
        }
    }
    else
    {
    m_currentFrame = MOUSE_OUT;
    }
}

void MenuButton::clean()
{
    Object::clean();
}
