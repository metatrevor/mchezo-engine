#ifndef LEVEL_H_
#define LEVEL_H_

#include <vector>
#include <string>
#include "Layer.h"

//Holds information about tileset also called the spritesheet
struct TileSet
{
    int firstgridId;
    int tileWidth;
    int tileHeight;
    int spacing;
    int margin;
    int width;
    int height;
    int numColumns;
    std::string name;
};

//The level class holds a vector of tileset and layer objects

class Level
{
public:

    ~Level();

    //Update the layers
    void update();

    //Render the layers
    void render();

    std::vector<TileSet> *getTileSets()
    {
        return &m_tileSets;
    }

    std::vector<Layer*> *getLayers()
    {
        return &m_layers;
    }

private:
    std::vector<TileSet> m_tileSets;
    std::vector<Layer*> m_layers;

    friend class LevelParser;
    //The level is only to be initialised with LevelParser class
    Level()
    {}
};

#endif
