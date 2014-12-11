#ifndef STATE_H
#define STATE_H

#include "InputManager.h"

class State
{
public:
    virtual bool init() = 0;
    virtual void run() = 0;
    virtual void render() = 0;
    virtual void update()  = 0;
    virtual void handleEvents()  = 0;
    virtual void exit() = 0;
    virtual ~State(){}
    std::string getStateName(){return m_stateName;}
    std::string m_stateName;
};

#endif // STATE_H
