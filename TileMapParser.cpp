#include "TileMapParser.h"

bool TileMapParser::parseTileMapData(std::string tileMapDataFile, std::vector<TileMap>* tileMapLayers, int* mapSizeX, int* mapSizeY)
{
  //init an XML document to load into
  TiXmlDocument xmlDoc;
    
  //load the XML file given
  if(!xmlDoc.LoadFile(tileMapDataFile))
  {
    //if does not load then return and print error message
    std::cerr << "TileMapParser parseTileMapData():" << xmlDoc.ErrorDesc() << " " << tileMapDataFile << "\n";
    return false;
  }

  //MAP INFORMATION
  //get the root element of XML
  TiXmlElement* pRoot = xmlDoc.RootElement();

  //get the elements of the mapInfo child, holding map and tile size
  TiXmlElement* e = pRoot->FirstChildElement();

  //store these details in the Level's mapSize values
  e->Attribute("mapSizeX", mapSizeX);
  e->Attribute("mapSizeY", mapSizeY);
  
  //PARSE XML ENVIRONMENT TILEMAP LAYERS
  //while there is another sibling element (another tilemap layer))
  while (e->NextSiblingElement() != 0) {

    //get the next layer (first tileMap layer)
    e = e->NextSiblingElement();
     
    //create a new TileMap
    TileMap newTileMapLayer;

    //fill it in with details
    e->Attribute("tileSizeX", &newTileMapLayer.tileSizeX);
    e->Attribute("tileSizeY", &newTileMapLayer.tileSizeY);
    e->Attribute("parallaxScrollSpeedX", &newTileMapLayer.parallaxScrollSpeedX);
    e->Attribute("parallaxScrollSpeedY", &newTileMapLayer.parallaxScrollSpeedY);
    e->Attribute("spritesheetNumColumns", &newTileMapLayer.spritesheetNumColumns);
    newTileMapLayer.spritesheetDataFileLocation = e->Attribute("spritesheetLocation");
    newTileMapLayer.spritesheetDataFileName = e->Attribute("spritesheetName");

    //add the texture to the renderer
    addTexture(newTileMapLayer.spritesheetDataFileLocation, newTileMapLayer.spritesheetDataFileName);
    
    //string to store tileSpriteIndex before being parsed
    std::string unparsedTileSpriteIndexData;

    //save the indexes to the string
    unparsedTileSpriteIndexData = e->Attribute("tileSpriteIndex");

    //pass to method to parse and save indexes into tilemap vector
    newTileMapLayer.tileSpriteIndexes = parseTileIndexes(unparsedTileSpriteIndexData);
    
    //save it in Level's vector of layers as an additional layer
    tileMapLayers->push_back(newTileMapLayer);
  }
   
  //CAMERA SETUP
  int tileSizeX, tileSizeY;
  e->Attribute("tileSizeX", &tileSizeX);
  e->Attribute("tileSizeY", &tileSizeY);
  
  //save the size of the map within the camera
  TheCamera::Instance()->setMapWidth(*mapSizeX * tileSizeX);
  TheCamera::Instance()->setMapHeight(*mapSizeY * tileSizeY);
}

std::vector<unsigned> TileMapParser::parseTileIndexes(std::string unparsedTileSpriteIndexData)
{  
  std::vector<unsigned> tileSpriteIndexes;
  
  do { //while unparsedTileSpriteIndexData still has characters in it

    //variable to hold the spritesheet index currently being parsed
    std::string index;

    //while first character in the unparsed string of indexes is a number
    while (isdigit(unparsedTileSpriteIndexData.front()))
    {
      //append the first character in unparsedTileSpriteIndexData to index
      index.append(unparsedTileSpriteIndexData, 0 , 1);
      //then remove that first char from unparsedTileSpriteIndexData
      unparsedTileSpriteIndexData.erase(unparsedTileSpriteIndexData.begin());
    }

    //convert string to int, and add to back of tileSpriteIndexes
    tileSpriteIndexes.push_back(atoi(index.c_str()));

    //if there are still more indexes to retrieve 
    if (unparsedTileSpriteIndexData.length() > 0)
    {
      //then while the next char is not a number for an index, the next char is a " "
      while (!isdigit(unparsedTileSpriteIndexData.front()))
      {
        //remove that space
        unparsedTileSpriteIndexData.erase(unparsedTileSpriteIndexData.begin());
      }
    } //until all spaces are removed

    //and loop again while unparsedTileSpriteIndexData to retrieve the next index, while still has characters in it
  } while (unparsedTileSpriteIndexData.length() > 0);

  //return the vector of parsed tile sprite indexes
  return tileSpriteIndexes;
}


bool TileMapParser::parseGameObjectData(std::string gameObjectsDataFile, std::vector<GameObject*>* gameObjects)
{
  //init an XML document to load into
  TiXmlDocument xmlDoc;
    
  //load the XML file given
  if(!xmlDoc.LoadFile(gameObjectsDataFile))
  {
    //if does not load then return and print error message
    std::cerr << "TileMapParser parseGameObjectData():" << xmlDoc.ErrorDesc() << " " << gameObjectsDataFile << "\n";
    return false;
  }

  //PARSE XML GAMEOBJECTS
  //get the root element of XML
  TiXmlElement* pRoot = xmlDoc.RootElement();

  //get the first element, the first GameObject defined in the file
  TiXmlElement* e = pRoot->FirstChildElement();

  //while there is another sibling (another gameObject to create)
  while (e != 0)
  {
    //create variables to hold the data that will be loaded into the object
    int x, y, width, height, spritesheetNumColumns;

    //fill them in with data from the file
    e->Attribute("x", &x);
    e->Attribute("y", &y);
    e->Attribute("width",&width);
    e->Attribute("height", &height);
    e->Attribute("spritesheetNumColumns", &spritesheetNumColumns);

    //get the name and file address, and add the texture for the object to the renderer
    std::string location  = e->Attribute("spritesheetLocation");
    std::string name = e->Attribute("spritesheetName");
    addTexture(location, name);

    //using the factory create and return an instance of the defined object
    GameObject* pGameObject = TheGameObjectFactory::Instance()->create(e->Attribute("type"));

    //load the XML data into the newly created object
    if (strcmp(e->Attribute("type"), "EnemyLevel01") == 0)
    {
      int startPosX, startPosY, endPosX, endPosY;
      e->Attribute("startPosX", &startPosX);
      e->Attribute("startPosY", &startPosY);
      e->Attribute("endPosX", &endPosX);
      e->Attribute("endPosY", &endPosY);

      pGameObject->load(new LoaderParams(x, y, width, height, name, spritesheetNumColumns,
                                         Vector2D(startPosX,startPosY),
                                         Vector2D(endPosX,endPosY)));

    }
    else
      pGameObject->load(new LoaderParams(x, y, width, height, name, spritesheetNumColumns));

    //add to the Level's list of GameObjects
    gameObjects->push_back(pGameObject);
        
    //get the next layer (should there be one)
    e = e->NextSiblingElement();
  }
  return true;
}


void TileMapParser::addTexture(std::string fileName, std::string textureID)
{
  TheRenderManager::Instance()->load(fileName, textureID, TheGame::Instance()->getRenderer());
}
