#ifndef LEVEL_H_
#define LEVEL_H_

#include <vector>
#include <string>
#include "Layer.h"
#include <tinyxml2.h>

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

    Level()
    {}

    ~Level();

    //Update the layers
    void update();

    //Render the layers
    void render();

    Level *parseLevel(const char *levelFile);

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


    void parseTileSets( tinyxml2::XMLElement  *tileSetRoot,
                        std::vector<TileSet> *tileSets);
    void parseTileLayer(tinyxml2::XMLElement *tileElement,
                        std::vector<Layer*> *layers,
                        const std::vector<TileSet>* tileSets);
    void parseTextures(tinyxml2::XMLElement  *textureRoot);
    void parseObjectLayer(tinyxml2::XMLElement *objectElement,
                          std::vector<Layer*> *layers);

    int m_tileSize;      //Tile width in px
    int m_width_columns; //Tile columns
    int m_height_rows;   //Tile rows

};

#endif
