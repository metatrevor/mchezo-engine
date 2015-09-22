#ifndef TILELAYER_H_
#define TILELAYER_H_

#include <vector>
#include <Tmx.h>
#include "Layer.h"
#include "Vector2D.h"
#include "Level.h"

//Extends the abstract layer class and holds data for the tile layer

class TileLayer : public Layer
{
public:
    TileLayer(int tileSize, const Tmx::Map *map, int index);

    virtual void update();

    virtual void render();

    virtual ~TileLayer()
    { }

    //Set the tile ids after parsing the layer data
    void setTileIDs(const std::vector<std::vector<int> > &data)
    {
        m_tileIDs = data;
    }

    void setTileSize(int tileSize)
    {
        m_tileSize = tileSize;
    }

    const Tmx::Tileset *getTileSetByID(int tileID);

private:

    int m_tileSize;

    //The vectors are used for map scrolling
    Vector2D m_position;
    Vector2D m_velocity;

    //Tile id data
    int index;
    const Tmx::Map *m_map;
    std::vector<std::vector<int> > m_tileIDs;
};

#endif
