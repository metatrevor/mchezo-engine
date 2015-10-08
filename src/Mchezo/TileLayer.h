#ifndef TILELAYER_H_
#define TILELAYER_H_

#include <vector>
#include <tmxparser/Tmx.h>
#include "Layer.h"
#include "Vector2D.h"
#include "Level.h"

//Extends the abstract layer class and holds data for the tile layer

class TileLayer : public Layer
{
public:
    TileLayer(const Tmx::Map *map, int index);

    virtual void update();

    virtual void render();

    virtual ~TileLayer()
    { }

    const Tmx::Tileset *getTileSetByID(int tileID);

private:

    //The vectors are used for map scrolling
    Vector2D m_position;
    Vector2D m_velocity;

    //Tile id data
    int index;
    //The map ptr
    const Tmx::Map *m_map;
};

#endif
