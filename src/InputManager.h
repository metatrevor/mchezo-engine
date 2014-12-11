#ifndef _INPUTMANAGER_H_
#define _INPUTMANAGER_H_

#include <iostream>
#include <vector>

#include <SDL2/SDL.h>
#include "Vector2D.h"

enum mouse_buttons
{
    LEFT = 0,
    MIDDLE = 1,
    RIGHT = 2
};

class InputManager
{
public:

    static InputManager &instance();

    void reset();

    // update and clean the input handler
    void update();

    // keyboard events
    bool isKeyDown(SDL_Scancode key) const;

    // mouse events
    bool getMouseButtonState(int buttonNumber) const;
    Vector2D* getMousePosition() const;

    bool onQuit();

private:

    InputManager();
    ~InputManager();

    InputManager(const InputManager&);
    InputManager& operator=(const InputManager&);

    // private functions to handle different event types


    // handle keyboard events
    void onKeyDown();
    void onKeyUp();

    // handle mouse events
    void onMouseMove(SDL_Event& event);
    void onMouseButtonDown(SDL_Event& event);
    void onMouseButtonUp(SDL_Event& event);


    // keyboard specific
    const Uint8* m_keystates;

    // mouse specific
    std::vector<bool> m_mouseButtonStates;
    Vector2D* m_mousePosition;

    //Event loop quit status
    bool m_eventLoopQuit;
};

#endif
