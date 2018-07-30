#ifndef _TileMapParser_
#define _TileMapParser_

#include "TileMap.h"

#include "GameObject.h"
#include "GameObjectFactory.h"
#include "tinyxml.h"

#include <iostream>
#include <vector>
#include <string>

class TileMapParser
{
public:
  //retrieves data for map size, background tiles, spritesheets 
  bool parseTileMapData(std::string tileMapDataFile, std::vector<TileMap>* tileMapLayers, int* mapSizeX, int* mapSizeY);

  //returns a vector of strings containing the sprite index of each tile in the spritesheet
  //data is parsed out of a single string value from the XML file
  std::vector<unsigned> parseTileIndexes(std::string tileMapIndexes);

  //calls load() for the renderer, adding the given texture
  void addTexture(std::string fileName, std::string textureID);
  
  //retrieves and calls to instantiate gameObjects for the level
  bool parseGameObjectData(std::string gameObjectsDataFile, std::vector<GameObject*>* gameObjects);

};
#endif
