#ifndef LEVEL_H_
#define LEVEL_H_

#include <vector>
#include <string>
#include "Layer.h"
#include <tinyxml2.h>
#include <Tmx.h>

//The level class holds a vector of tileset and layer objects

class Level
{
public:

    Level()
    {}

    ~Level();

    //Update the layers
    void update();

    //Render the layers
    void render();

    Level *parseLevel(const char *levelFile);

    std::vector<Layer*> *getLayers()
    {
        return &m_layers;
    }

private:
    std::vector<Layer*> m_layers;

    void parseTileLayer(tinyxml2::XMLElement *tileElement,
                        std::vector<Layer*> *layers,
                        const std::vector< Tmx::Tileset* > &tileSets,
                        int index);
    void parseObjectLayer(tinyxml2::XMLElement *objectElement,
                          std::vector<Layer*> *layers);

    int m_tileSize;      //Tile width in px
    int m_width_columns; //Tile columns
    int m_height_rows;   //Tile rows
    Tmx::Map *m_map;
};

#endif
