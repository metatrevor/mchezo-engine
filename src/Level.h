#ifndef LEVEL_H_
#define LEVEL_H_

#include <vector>
#include <string>
#include "Layer.h"

struct Tileset
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

class Level
{
public:
    Level();
    ~Level();

    void update();
    void render();

    std::vector<Tileset> *getTilesets() { return &m_tilesets; }
    std::vector<Layer*> *getLayers(){return &m_layers;}

private:
    std::vector<Tileset> m_tilesets;
    std::vector<Layer*> m_layers;
};

#endif
