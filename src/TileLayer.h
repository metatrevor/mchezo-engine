#ifndef TILELAYER_H_
#define TILELAYER_H_

#include <vector>
#include "Layer.h"
#include "Vector2D.h"
#include "Level.h"

//Extends the abstract layer class and holds data for the tile layer

class TileLayer : public Layer
{
public:
    TileLayer(int tileSize, const std::vector<TileSet> &tileSets);

    virtual void update();
    virtual void render();

    virtual ~TileLayer(){}

    //Set the tile ids after parsing the layer data
    void setTileIDs(const std::vector<std::vector<int> > &data)
    {
        m_tileIDs = data;
    }

    void setTileSize(int tileSize)
    {
        m_tileSize = tileSize;
    }

    TileSet getTileSetByID(int tileID);
private:

    int m_numColumns; //No of columns for game
    int m_numRows;  //No of rows for game
    int m_tileSize;

    //The vectors are used for map scrolling
    Vector2D m_position;
    Vector2D m_velocity;

    //Tile set data
    const std::vector<TileSet> &m_tileSets;

    //Tile id data
    std::vector<std::vector<int> > m_tileIDs;
};

#endif
