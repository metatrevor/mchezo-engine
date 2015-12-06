#ifndef LEVEL_H_
#define LEVEL_H_

#include <vector>
#include <string>
#include <tinyxml2.h>
#include "Layer.h"
#include <tmxparser/Tmx.h>

// The level class holds a ptr to the map, objects and custom layers
// Referenced to the layers in map by with an index

class Level
{
public:

    Level()
    { }

    ~Level();

    //Update the layers
    void update();

    //Render the layers
    void render();

    void parseLevel(const char *levelFile);

    std::vector<Layer *> *getLayers()
    {
        return &m_layers;
    }

private:
    std::vector<Layer *> m_layers;

    Tmx::Map *m_map;
};

#endif
