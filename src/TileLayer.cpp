#include "TileLayer.h"
#include "TextureManager.h"
#include "Log.h"

//Initialize the layer object and set the level tile dimensions
TileLayer::TileLayer(int tileSize, const std::vector<TileSet> &tileSets) :
    m_tileSize(tileSize),
    m_tileSets(tileSets),
    m_position(0,0),
    m_velocity(0,0)
{
    m_numColumns = 640 / m_tileSize;  //getgamewidth
    m_numRows = 480 / m_tileSize;     //getgameheight
}

void TileLayer::update()
{
    m_position += m_velocity;
    m_velocity.setX(1);
}

//Render the tiles

void TileLayer::render()
{
    int x, y, x2, y2 = 0;

    x = int(m_position.getX())/m_tileSize;
    y = int(m_position.getY())/m_tileSize;

    x2 = int(m_position.getX()) % m_tileSize;
    y2 = int(m_position.getY()) % m_tileSize;

    for (int i = 0; i < m_numRows; ++i) {
        for (int j = 0; j < m_numColumns; ++j) {

            //Get the tile ID
            int id = m_tileIDs[i][j+x];

            //Do not render null tile id's
            if(id==0)
            {
                continue;
            }

            TileSet tileset = getTileSetByID(id);

            id--;
            TextureManager::instance().drawTile(
                    tileset.name,
                    tileset.margin,
                    tileset.spacing,
                    (j * m_tileSize) - x2, //The position to draw the tile at x
                    (i * m_tileSize) - y2, //The position to draw the tile at y
                    m_tileSize,
                    m_tileSize,
                    (id - (tileset.firstgridId - 1)) / tileset.numColumns, //Get location of tile on the worksheet
                    (id - (tileset.firstgridId - 1)) % tileset.numColumns); //Get location of tile on the worksheet
        }
    }
}

//Get the tileset for the tile id
TileSet TileLayer::getTileSetByID(int tileID)
{
    for(int i = 0; i < m_tileSets.size(); i++)
        {
            if( i + 1 <= m_tileSets.size() - 1)
            {
                if(tileID >= m_tileSets[i].firstgridId && tileID < m_tileSets[i + 1].firstgridId)
                {
                    return m_tileSets[i];
                }
            }
            else
            {
                return m_tileSets[i];
            }
        }
    Log::Error("Unable to find tileset, returning an empty tileset");
    TileSet t;
    return t;
}
