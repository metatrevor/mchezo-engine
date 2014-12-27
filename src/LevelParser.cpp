#include "LevelParser.h"
#include "TextureManager.h"
#include "TileLayer.h"
#include "common/base64/base64.h"
#include "zlib.h"
#include "ObjectLayer.h"
#include "Object.h"


Level *LevelParser::parseLevel(const char *levelFile)
{
    //Load the map file
    tinyxml2::XMLDocument levelDocument;
    levelDocument.LoadFile(levelFile);
    Level *level = new Level();

    //Load root node
    tinyxml2::XMLElement *root = levelDocument.RootElement();

    //Load map info
    root->QueryIntAttribute("tilewidth", &m_tileSize); //Tile width in pixels
    root->QueryIntAttribute("width", &m_width_columns); //No of columns
    root->QueryIntAttribute("height", &m_height_rows); //No of rows

    //Parse the tilesets
    for (tinyxml2::XMLElement *e = root->FirstChildElement(); e != NULL; e = e->NextSiblingElement()) {
        if (e->Value() == std::string("tileset")) {
            parseTileSets(e, level->getTileSets());
        }
    }
    //Parse tile layers
    for (tinyxml2::XMLElement *e = root->FirstChildElement(); e != NULL; e = e->NextSiblingElement()) {
        if (e->Value() == std::string("layer") || e->Value() == std::string("objectgroup")) {

            if(e->FirstChildElement()->Value() == std::string("object")) {
                parseObjectLayer(e, level->getLayers());
            }
            else if(e->FirstChildElement()->Value() == std::string("data")) {
                parseTileLayer(e, level->getLayers(), level->getTileSets());
            }
        }
    }

    return level;
}

void LevelParser::parseTileSets(tinyxml2::XMLElement *tileSetRoot, std::vector<TileSet> *tileSets)
{
    TextureManager::instance().loadTexture(tileSetRoot->Attribute("name") ,(std::string)"assets/textures/"+tileSetRoot->FirstChildElement()->Attribute("source"));

    TileSet tileSet;

    //Load tileset attributes
    tileSetRoot->QueryIntAttribute("firstgid", &tileSet.firstgridId);
    tileSet.name = tileSetRoot->Attribute("name");
    tileSetRoot->QueryIntAttribute("tilewidth", &tileSet.tileWidth);
    tileSetRoot->QueryIntAttribute("tileheight", &tileSet.tileHeight);
    tileSetRoot->QueryIntAttribute("spacing", &tileSet.spacing);
    tileSetRoot->QueryIntAttribute("margin", &tileSet.margin);

    //Load tileset image attributes
    tileSetRoot->FirstChildElement()->QueryIntAttribute("width" , &tileSet.width);
    tileSetRoot->FirstChildElement()->QueryIntAttribute("height", &tileSet.height);

    //Calculate the tileset columns taking into account the image width & spacing
    tileSet.numColumns = tileSet.width / (tileSet.tileWidth + tileSet.spacing);

    tileSets->push_back(tileSet);
}


void LevelParser::parseTileLayer(tinyxml2::XMLElement *tileElement, std::vector<Layer*>*layers, const std::vector<TileSet> *tileSets)
{

    TileLayer *tileLayer = new TileLayer(m_tileSize, *tileSets);

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

//Parse the level textures
void LevelParser::parseTextures(tinyxml2::XMLElement *textureRoot)
{
    TextureManager::instance().loadTexture(textureRoot->Attribute("name"),
    (std::string)"assets/textures/"+textureRoot->FirstChildElement()->Attribute("source"));
}

//Parse object layers
void LevelParser::parseObjectLayer(tinyxml2::XMLElement *objectElement, std::vector<Layer*> *layers)
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
