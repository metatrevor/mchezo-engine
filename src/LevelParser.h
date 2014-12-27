#ifndef LEVELPARSER_H_
#define LEVELPARSER_H_

#include "Level.h"
#include <tinyxml2.h>


class LevelParser
{
public:
    Level *parseLevel(const char *levelFile);

private:

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

