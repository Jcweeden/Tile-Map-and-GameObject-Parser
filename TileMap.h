#ifndef _TileMap_
#define _TileMap_

#include <ctype.h> //isdigit()
#include <vector>
#include <string>

class TileMap
{
public:
  //pixel size of each individual tile
  int tileSizeX;
  int tileSizeY;

  //speed at which the tiles scroll across the screen
  //default value is 100, for no parallax scrolling
  int parallaxScrollSpeedX;
  int parallaxScrollSpeedY;

  //number of the columns on the spritesheet
  int spritesheetNumColumns;

  //file address of spritesheet file used to draw elements in this tilemap
  std::string spritesheetDataFileLocation;

  //name used as ID to draw the sprites in the RenderManager 
  std::string spritesheetDataFileName;

  //parsed from xml, stores the index of the sprite to be drawn in the tile from the spritesheet
  std::vector<unsigned> tileSpriteIndexes;
};

#endif
