#include "TileLayer.h"
#include "TextureManager.h"

//Initialize the layer object and set the level tile dimensions
TileLayer::TileLayer(const Tmx::Map *map, int index) :
        m_position(0, 0),
        m_velocity(0, 0),
        index(index),
        m_map(map)
{ }

void TileLayer::update()
{
    m_position += m_velocity;
    m_velocity.setX(1);
}

//Render the tiles

void TileLayer::render()
{
    int x, y, x2, y2 = 0;

    x = int(m_position.getX()) / m_map->GetTileWidth();
    y = int(m_position.getY()) / m_map->GetTileWidth();;

    x2 = int(m_position.getX()) % m_map->GetTileWidth();;
    y2 = int(m_position.getY()) % m_map->GetTileWidth();;

    for (int i = 0; i < m_map->GetLayer(index)->GetHeight(); ++i) {
        for (int j = 0; j < m_map->GetLayer(index)->GetWidth(); ++j) {

            //Get the tile ID
            int id = m_map->GetTileLayer(index)->GetTileGid(i + y, j + x);
            //Do not render null tile id's
            if (id == 0) {
                continue;
            }

            const Tmx::Tileset *tileset = getTileSetByID(id);

            if (tileset == nullptr)
                continue;

            id--;
            TextureManager::instance().drawTile(
                    tileset->GetName(),
                    tileset->GetMargin(),
                    tileset->GetSpacing(),
                    (j * m_map->GetTileWidth()) - x2, //The position to draw the tile at x
                    (i * m_map->GetTileWidth()) - y2, //The position to draw the tile at y
                    m_map->GetTileWidth(),
                    m_map->GetTileWidth(),
                    (id - (tileset->GetFirstGid() - 1)) / (tileset->GetImage()->GetWidth() / (tileset->GetTileWidth() +
                                                                                              tileset->GetSpacing())), //Get location of tile on the worksheet
                    (id - (tileset->GetFirstGid() - 1)) % tileset->GetImage()->GetHeight() /
                    (tileset->GetTileHeight() + tileset->GetSpacing())); //Get location of tile on the worksheet
            // numcolumns = tileset.GetImage()->GetWidth() / (tileset.GetTileWidth() + tileset.GetSpacing())
        }
    }
}

//Get the tileset for the tile id
const Tmx::Tileset *TileLayer::getTileSetByID(int tileID)
{
    for (int i = 0; i < m_map->GetNumTilesets(); i++) {
        if (i + 1 <= m_map->GetNumTilesets() - 1) {
            if (tileID >= m_map->GetTileset(i)->GetFirstGid() && tileID < m_map->GetTileset(i + 1)->GetFirstGid()) {
                return m_map->GetTileset(i);
            }
        }
        else {
            return m_map->GetTileset(i);
        }
    }
    Log::Error("Unable to find tileset, returning a null ptr");
    return nullptr;
}
