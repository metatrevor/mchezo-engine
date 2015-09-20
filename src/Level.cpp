#include "Level.h"
#include "TextureManager.h"
#include "zlib.h"
#include "TileLayer.h"
#include "common/base64/base64.h"
#include "ObjectLayer.h"



Level::~Level()
{

}


void Level::render()
{
    std::vector<Layer*>::size_type i;
    for (i = 0; i < m_layers.size(); ++i)
    {
        m_layers[i]->render();
    }
}

void Level::update()
{
    std::vector<Layer*>::size_type i;
    for (i = 0; i < m_layers.size(); ++i) {
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
        switch(m_map->GetErrorCode()){
            case Tmx::MapError::TMX_COULDNT_OPEN: {
                Log::Error("The Map Couldn't be opened");
                break;
            }

            case Tmx::MapError::TMX_INVALID_FILE_SIZE:
            {
                Log::Error("Invalid file size");
                break;
            }

            case Tmx::MapError::TMX_PARSING_ERROR:
            {
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

    //Load map info
    m_tileSize = m_map->GetTileWidth();
    m_width_columns = m_map->GetWidth();
    m_height_rows = m_map->GetHeight();

    //Parse the tilesets

    for(int i = 0; i < m_map->GetNumTilesets(); ++i) {

        const Tmx::Tileset *tileSet = m_map->GetTileset(i);

        TextureManager::instance().loadTexture(tileSet->GetName() ,(std::string)"assets/textures/"+tileSet->GetImage()->GetSource());
    }


    //Parse tile layers
    for (tinyxml2::XMLElement *e = root->FirstChildElement(); e != NULL; e = e->NextSiblingElement()) {
        if (e->Value() == std::string("layer") || e->Value() == std::string("objectgroup")) {

            if(e->FirstChildElement()->Value() == std::string("object")) {
                parseObjectLayer(e, this->getLayers());
            }
            else if(e->FirstChildElement()->Value() == std::string("data")) {
                parseTileLayer(e, this->getLayers(), m_map->GetTilesets());
            }
        }
    }
}

void Level::parseTileLayer(tinyxml2::XMLElement *tileElement, std::vector<Layer*>*layers, const std::vector< Tmx::Tileset* > &tileSets)
{

    TileLayer *tileLayer = new TileLayer(m_tileSize, tileSets);

    //Multidimesional int array to hold the decoded uncompresssed tile id data
    std::vector<std::vector<int> > data;
    //Stores the decoded base64 string
    std::string decodedIDs;
    //Stores the layer data node
    tinyxml2::XMLElement *dataNode;

    //Find the layer data node
    for (tinyxml2::XMLElement *e = tileElement->FirstChildElement(); e != NULL; e = e->NextSiblingElement()) {
        if (e->Value() == std::string("data")) {
            dataNode = e;
        }
    }

    //Get the compressed base64 string and decode it
    //TODO: eliminate the loop below
    for (tinyxml2::XMLNode *e = dataNode->FirstChild(); e != NULL; e = e->NextSibling()) {
        tinyxml2::XMLText *text = e->ToText();
        std::string t = tinyxml2::XMLUtil::SkipWhiteSpace(text->ToText()->Value());
        decodedIDs = base64_decode(t);
    }

    //Get the size the memory size for the ids
    uLongf sizeOfIds = m_width_columns * m_height_rows * sizeof(int);
    //Get the number of tile id's
    std::vector<int> ids(m_width_columns * m_height_rows);
    //Do the actual zlib decompression
    uncompress((Bytef*) &ids[0], &sizeOfIds, (const Bytef*)decodedIDs.c_str(), decodedIDs.size());

    //Create empty layer row arrays and insert them to the main data array
    std::vector<int> layerRow(m_width_columns);
    for (int j = 0; j < m_height_rows; j++) {
        data.push_back(layerRow);
    }

    //Fill the data array with the tile ids
    for (int rows = 0; rows < m_height_rows; ++rows) {
        for (int columns = 0; columns < m_width_columns; ++columns ) {
            data[rows][columns] = ids[rows * m_width_columns + columns];
        }
    }
    //Set the loaded tile data ids to the tilelayer
    tileLayer->setTileIDs(data);

    //Add the tilelayer to the level
    layers->push_back(tileLayer);
}


//Parse object layers
void Level::parseObjectLayer(tinyxml2::XMLElement *objectElement, std::vector<Layer*> *layers)
{
    //Create an object layer

    ObjectLayer *objectLayer = new ObjectLayer();
    Log::Info("Loading object : " + (std::string)objectElement->FirstChildElement()->Value());
    for(tinyxml2::XMLElement *e = objectElement->FirstChildElement(); e != NULL; e = e->NextSiblingElement())
    {
        Log::Info("Object value : " + (std::string)e->Value());
        if(e->Value() == std::string("object"))
        {
            int x, y, width, height, numFrames, callbackId, animSpeed;
            std::string textureId;
            //Get the initial values of x and y
            e->QueryIntAttribute("x", &x);
            e->QueryIntAttribute("y", &y);

            //Object *object = new

            //Get the property values
            for (tinyxml2::XMLElement *properties = e->FirstChildElement(); properties != NULL; properties = properties->NextSiblingElement()) {
                if (properties->Value() == std::string("properties")) {
                    for(tinyxml2::XMLElement* property = properties->FirstChildElement(); property != NULL; property = property->NextSiblingElement())
                    {
                        if(property->Value() == std::string("property")) {
                            if(property->Attribute("name") == std::string("numFrames")) {
                                property->QueryIntAttribute("value", &numFrames);
                            }
                            else if(property->Attribute("name") == std::string("textureHeight")) {
                                property->QueryIntAttribute("value", &height);
                            }
                            else if(property->Attribute("name") == std::string("textureID")) {
                                textureId = property->Attribute("value");
                            }
                            else if(property->Attribute("name") == std::string("textureWidth")) {
                                property->QueryIntAttribute("value", &width);
                            }
                            else if(property->Attribute("name") == std::string("callbackID")) {
                                property->QueryIntAttribute("value", &callbackId);
                            }
                            else if(e->Attribute("name") == std::string("animSpeed")) {
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
