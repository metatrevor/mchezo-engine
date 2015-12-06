#include "Level.h"
#include "TextureManager.h"
#include "TileLayer.h"


Level::~Level()
{

}


void Level::render()
{
    for (int i = 0; i < m_map->GetNumLayers(); ++i) {
        m_layers[i]->render();
    }
}

void Level::update()
{
    for (int i = 0; i < m_map->GetNumLayers(); ++i) {
        m_layers[i]->update();
    }
}

void Level::parseLevel(const char *levelFile)
{
    //Load with TMX Parser

    m_map = new Tmx::Map();

    m_map->ParseFile(levelFile);

    if (m_map->HasError()) {
        Log::Error("Loading Map : " + m_map->GetErrorText());
        switch (m_map->GetErrorCode()) {
            case Tmx::MapError::TMX_COULDNT_OPEN: {
                Log::Error("The Map Couldn't be opened");
                break;
            }

            case Tmx::MapError::TMX_INVALID_FILE_SIZE: {
                Log::Error("Invalid file size");
                break;
            }

            case Tmx::MapError::TMX_PARSING_ERROR: {
                Log::Error("There was an error in parsing the map file");
                break;
            }

            default:
                break;
        }

        //TODO: Proper map loading error handling otherwise lets exit
        std::exit(0);
    }

    tinyxml2::XMLDocument levelDocument;
    levelDocument.LoadFile(levelFile);



    //Parse the tilesets

    for (int i = 0; i < m_map->GetNumTilesets(); ++i) {

        const Tmx::Tileset *tileSet = m_map->GetTileset(i);

        TextureManager::instance().loadTexture(tileSet->GetName(),
                                               (std::string) "assets/textures/" + tileSet->GetImage()->GetSource());
    }

    // Create internal layers for the map

    for (int i = 0; i < m_map->GetNumLayers(); ++i) {
        TileLayer *tileLayer = new TileLayer(m_map, i);
        m_layers.push_back(tileLayer);
    }

}
