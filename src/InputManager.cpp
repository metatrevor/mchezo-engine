#include "InputManager.h"


InputManager::InputManager() :
        m_keystates(0),
        m_mousePosition(new Vector2D(0, 0)),
        m_eventLoopQuit(false)
{
    // create button states for the mouse
    for (int i = 0; i < 3; i++) {
        m_mouseButtonStates.push_back(false);
    }
}

InputManager &InputManager::instance()
{
    static InputManager m_instance;
    return m_instance;
}

bool InputManager::onQuit()
{
    return m_eventLoopQuit;
}

InputManager::~InputManager()
{
    // delete anything we created dynamically
    delete m_keystates;
    delete m_mousePosition;

    m_mouseButtonStates.clear();
}


void InputManager::reset()
{
    m_mouseButtonStates[LEFT] = false;
    m_mouseButtonStates[RIGHT] = false;
    m_mouseButtonStates[MIDDLE] = false;
}

bool InputManager::isKeyDown(SDL_Scancode key) const
{
    if (m_keystates != 0) {
        if (m_keystates[key] == 1) {
            return true;
        }
        else {
            return false;
        }
    }

    return false;
}


bool InputManager::getMouseButtonState(int buttonNumber) const
{
    return m_mouseButtonStates[buttonNumber];
}

Vector2D *InputManager::getMousePosition() const
{
    return m_mousePosition;
}

void InputManager::update()
{
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        switch (event.type) {
            case SDL_QUIT:
                m_eventLoopQuit = true;
                break;

            case SDL_MOUSEMOTION:
                onMouseMove(event);
                break;

            case SDL_MOUSEBUTTONDOWN:
                onMouseButtonDown(event);
                break;

            case SDL_MOUSEBUTTONUP:
                onMouseButtonUp(event);
                break;

            case SDL_KEYDOWN:
                onKeyDown();
                break;

            case SDL_KEYUP:
                onKeyUp();
                break;

            default:
                break;
        }
    }
}

void InputManager::onKeyDown()
{
    m_keystates = SDL_GetKeyboardState(0);
}

void InputManager::onKeyUp()
{
    m_keystates = SDL_GetKeyboardState(0);
}

void InputManager::onMouseMove(SDL_Event &event)
{
    m_mousePosition->setX(event.motion.x);
    m_mousePosition->setY(event.motion.y);
}

void InputManager::onMouseButtonDown(SDL_Event &event)
{
    if (event.button.button == SDL_BUTTON_LEFT) {
        m_mouseButtonStates[LEFT] = true;
    }

    if (event.button.button == SDL_BUTTON_MIDDLE) {
        m_mouseButtonStates[MIDDLE] = true;
    }

    if (event.button.button == SDL_BUTTON_RIGHT) {
        m_mouseButtonStates[RIGHT] = true;
    }
}

void InputManager::onMouseButtonUp(SDL_Event &event)
{
    if (event.button.button == SDL_BUTTON_LEFT) {
        m_mouseButtonStates[LEFT] = false;
    }

    if (event.button.button == SDL_BUTTON_MIDDLE) {
        m_mouseButtonStates[MIDDLE] = false;
    }

    if (event.button.button == SDL_BUTTON_RIGHT) {
        m_mouseButtonStates[RIGHT] = false;
    }
}
