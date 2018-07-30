#ifndef _Level_
#define _Level_

#include "RenderManager.h"
#include "TileMap.h"
#include "TileMapParser.h"
#include "GameObject.h"
#include "Vector2D.h"
#include "Camera.h"
#include "Game.h"

#include <vector>
#include <string>

class GameObject;

class Level
{
public:
  //constructor
  Level();

  //parses the XML data file to populate tilesLayers with data for each tileset
  //and parses data file detailing GameObjects to be instantiated, creating them and storing
  //them in the gameObjects vector
  void setupLevel(std::string tileMapDataFile, std::string gameObjectsDataFile = "");
  
  //calls the update function for each GameObject
  void update();

  //draws each GameObject on top of the tileLayers that form the background
  void draw();

  //deletes any pointer creates within the level
  void clean();

  //draws a single tilemap layer without any parallax scrolling
  void drawTileMap(TileMap* tilemap);
  //draws a single tilemap layer, adjusting the object's positions according to the parallax value
  void drawTileMapWithParallax(TileMap* tilemap);


public:

  //size of the map (in tiles)
  int mapSizeX;
  int mapSizeY;

  //contains all info to draw the background
  std::vector<TileMap> tilesLayers;

  //contains all GameObjects within the level
  std::vector<GameObject*> gameObjects;

};

#endif
