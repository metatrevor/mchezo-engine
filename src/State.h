#ifndef STATE_H
#define STATE_H

#include "InputManager.h"
#include "Object.h"

class State
{
public:
    virtual bool init() = 0;
    virtual void run();
    virtual void render();
    virtual void update();
    virtual void handleEvents();
    virtual void exit() = 0;
    virtual ~State(){}
    std::string getStateName(){return m_stateName;}
    std::string m_stateName;
    std::vector<Object*> m_objects;
};

#endif // STATE_H

