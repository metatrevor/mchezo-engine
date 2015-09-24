#include "Level.h"
#include "TextureManager.h"
#include "zlib.h"
#include "TileLayer.h"
#include "ObjectLayer.h"


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

Level *Level::parseLevel(const char *levelFile)
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


    //Load root node
    tinyxml2::XMLElement *root = levelDocument.RootElement();

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

    //Parse tile layers
    for (tinyxml2::XMLElement *e = root->FirstChildElement(); e != NULL; e = e->NextSiblingElement()) {
        if (e->Value() == std::string("layer") || e->Value() == std::string("objectgroup")) {

            if (e->FirstChildElement()->Value() == std::string("object")) {
                parseObjectLayer(e, this->getLayers());
            }
        }
    }
}

//Parse object layers
void Level::parseObjectLayer(tinyxml2::XMLElement *objectElement, std::vector<Layer *> *layers)
{
    //Create an object layer

    ObjectLayer *objectLayer = new ObjectLayer();
    Log::Info("Loading object : " + (std::string) objectElement->FirstChildElement()->Value());
    for (tinyxml2::XMLElement *e = objectElement->FirstChildElement(); e != NULL; e = e->NextSiblingElement()) {
        Log::Info("Object value : " + (std::string) e->Value());
        if (e->Value() == std::string("object")) {
            int x, y, width, height, numFrames, callbackId, animSpeed;
            std::string textureId;
            //Get the initial values of x and y
            e->QueryIntAttribute("x", &x);
            e->QueryIntAttribute("y", &y);

            //Object *object = new

            //Get the property values
            for (tinyxml2::XMLElement *properties = e->FirstChildElement();
                 properties != NULL; properties = properties->NextSiblingElement()) {
                if (properties->Value() == std::string("properties")) {
                    for (tinyxml2::XMLElement *property = properties->FirstChildElement();
                         property != NULL; property = property->NextSiblingElement()) {
                        if (property->Value() == std::string("property")) {
                            if (property->Attribute("name") == std::string("numFrames")) {
                                property->QueryIntAttribute("value", &numFrames);
                            }
                            else if (property->Attribute("name") == std::string("textureHeight")) {
                                property->QueryIntAttribute("value", &height);
                            }
                            else if (property->Attribute("name") == std::string("textureID")) {
                                textureId = property->Attribute("value");
                            }
                            else if (property->Attribute("name") == std::string("textureWidth")) {
                                property->QueryIntAttribute("value", &width);
                            }
                            else if (property->Attribute("name") == std::string("callbackID")) {
                                property->QueryIntAttribute("value", &callbackId);
                            }
                            else if (e->Attribute("name") == std::string("animSpeed")) {
                                property->QueryIntAttribute("value", &animSpeed);
                            }
                        }
                    }
                }
            }
            //object->load(new LoaderParams(x, y, width, height, textureID,numFrames, callbackID, animSpeed));
            //objectLayer->getGameObjects()->push_back(pGameObject);
        }
    }
    layers->push_back(objectLayer);
}
