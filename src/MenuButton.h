#ifndef MENUBUTTON_H
#define MENUBUTTON_H

#include "Object.h"

enum button_state
{
    MOUSE_OUT = 0,
    MOUSE_OVER = 1,
    CLICKED = 2
};

class MenuButton : public Object
{
public:
    MenuButton(int x, int y, int height, int width, std::string textureKeyName, void(*callback)());
    virtual void draw();
    virtual void update();
    virtual void clean();
private:
    void(*m_callback)();
    bool m_released;
};

#endif // MENUBUTTON_H
