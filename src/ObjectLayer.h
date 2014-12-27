#ifndef OBJECTLAYER_H
#define OBJECTLAYER_H

#include "Layer.h"
#include "Object.h"
#include <vector>

class ObjectLayer : public Layer
{
public:
    virtual void update();
    virtual void render();

    std::vector<Object*>* getGameObjects()
    {
        return &m_gameObjects;
    }
private:
    std::vector<Object*> m_gameObjects;
};

#endif // OBJECTLAYER_H
