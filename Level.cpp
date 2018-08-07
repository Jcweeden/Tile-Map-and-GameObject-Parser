#include "Level.h"
#include "InputHandler.h"

Level::Level()
{
  std::vector<TileMap> tilesLayers;
  std::vector<GameObject*> gameObjects;
}


void Level::setupLevel(std::string tileMapDataFile, std::string gameObjectsDataFile)
{
  std::cout << "Level.cpp setupLevel():setupLevel()\n";
  //create instance of parser to retrieve tilemap data and gameObjects data from XMLs
  TileMapParser tmp;

  //TILE-MAP PARSING
  tmp.parseTileMapData(tileMapDataFile, &tilesLayers, &mapSizeX, &mapSizeY);
  
  //GAMEOBJECTS PARSING
  //if there is a file of gameObject data to be parsed
  if (gameObjectsDataFile != "")
    //pass in the gameObjects vector, where all gameObjects will be stored
    tmp.parseGameObjectData(gameObjectsDataFile, &gameObjects);

  //uncomment to set to the camera to follow the mouse cursor
  //TheCamera::Instance()->setTarget(TheInputHandler::Instance()->getMousePosition());
  //TheCamera::Instance()->setPosition(TheInputHandler::Instance()->getMousePosition());
}

void Level::update()
{
  for (size_t i = 0; i < gameObjects.size(); i++) {
    gameObjects[i]->update();
  }
}

void Level::draw()
{
  //draw each layer of the environment
  for (size_t i = 0; i < tilesLayers.size(); i++)
  {
    //if tilemap does not has parallax values
    if (tilesLayers[i].parallaxScrollSpeedX == 100 && tilesLayers[i].parallaxScrollSpeedY == 100)
      drawTileMap(&tilesLayers[i]); //draw normally
    else //the tilemap has parallax values
      drawTileMapWithParallax(&tilesLayers[i]); //run to draw with parallax
  }

  //draw gameObjects in the level
  for (size_t i = 0; i < gameObjects.size(); i++) {

    if(gameObjects[i]->getPosition().getX() <= TheCamera::Instance()->getPosition().getX() + TheGame::Instance()->getWindowWidth())
    {
      gameObjects[i]->draw();
    }
  }
}

void Level::clean()
{
  //delete all GameObjects in the level
  for (size_t i; i < gameObjects.size(); i++) {
    gameObjects[i]->clean();
  }
  gameObjects.clear();
}

void Level::drawTileMap(TileMap* tilemap)
{
  //for each tile across the map's x and y axis
  for (size_t y = 0; y < mapSizeY; y++)
  {
    for (size_t x = 0; x < mapSizeX; x++)
    {
      //if the tile is not to be ignored (signified by index 99) - continue to render the tile
      if (tilemap->tileSpriteIndexes[(y * mapSizeX) + (x)] != 99) {
        //if the tile is within the view of the camera's current x position - continue to render the tile
        //if !(x * tileSize) < -tileSize     //(-tileSize (rather than 0) draws an additional tile to account for the half tiles on each side of the screen)
        //if !(x * tileSize) > windowWidth  //if within the width of the window
        if (!((x * tilemap->tileSizeX) - (TheCamera::Instance()->getPosition().getX()) < -(tilemap->tileSizeX) ||
              (x * tilemap->tileSizeX) - (TheCamera::Instance()->getPosition().getX()) > TheGame::Instance()->getWindowWidth()))
        {

          //if the tile is within the view of the camera's current y position - continue to render the tile
          //run same checks but this time for the y axis height of the screen
          if (!((y * tilemap->tileSizeY) - (TheCamera::Instance()->getPosition().getY()) < -(tilemap->tileSizeY) ||
                (y * tilemap->tileSizeY) - (TheCamera::Instance()->getPosition().getY()) > TheGame::Instance()->getWindowHeight()))
          {
          
            //calculate the row/col index in the tilemap spritesheet for this current tile  
            int row = tilemap->tileSpriteIndexes[(y*mapSizeX) + (x)]
                % tilemap->spritesheetNumColumns; //modulo the width of the spritesheet to get the left over row index
            int col = (float)tilemap->tileSpriteIndexes[(y*mapSizeX) + (x)]
                / tilemap->spritesheetNumColumns; //divide by width and round down number to get the column index

            //call to draw the tile
            TheRenderManager::Instance()->drawTile(tilemap->spritesheetDataFileName, //ID
                                                    (x * tilemap->tileSizeX) - (TheCamera::Instance()->getPosition().getX()), //x
                                                    (y * tilemap->tileSizeY) - (TheCamera::Instance()->getPosition().getY()), //y
                                                    (int)row, //the row in the spritesheet at which the sprite is
                                                    (int)col, //column in spritesheet
                                                    tilemap->tileSizeX, //width
                                                    tilemap->tileSizeY, //height
                                                    TheGame::Instance()->getRenderer(), //renderer
                                                    SDL_FLIP_NONE);
          }
        }
      }
    }
  }
}

void Level::drawTileMapWithParallax(TileMap* tilemap)
{
  //for each tile across the map's x and y axis
  for (size_t y = 0; y < mapSizeY; y++)
  {
    for (size_t x = 0; x < mapSizeX; x++)
    {
      //if the tile is not to be ignored (signified by index 99) - continue to render the tile
      if (tilemap->tileSpriteIndexes[(y * mapSizeX) + (x)] != 99) {

        //if the tile is within the view of the camera's current x position - continue to render the tile
        //if !(x * tileSize) - (cameraPosition * parallaxScrollSpeed) < -tileSize     //(-tileSize (rather than 0) draws an additional tile to account for the half tiles on each side of the screen)
        //if !(x * tileSize) - (cameraPosition * parallaxScrollSpeed) > windowWidth   //if within the width of the window
        if (!((x * tilemap->tileSizeX) - ((gameObjects[0]->getPosition().getX() - TheGame::Instance()->getWindowWidth()/2) * (float)((float)tilemap->parallaxScrollSpeedX/100)) < -(tilemap->tileSizeX) ||
              (x * tilemap->tileSizeX) - ((gameObjects[0]->getPosition().getX() - TheGame::Instance()->getWindowWidth()/2) * (float)((float)tilemap->parallaxScrollSpeedX/100)) > TheGame::Instance()->getWindowWidth()))
        {
          //if the tile is within the view of the camera's current y position - continue to render the tile
          //run same checks but this time for the y axis height of the screen
          if (!((y * tilemap->tileSizeY) - (TheCamera::Instance()->getPosition().getY() * (float)((float)tilemap->parallaxScrollSpeedY/100)) < -(tilemap->tileSizeY) ||
                (y * tilemap->tileSizeY) - (TheCamera::Instance()->getPosition().getY() * (float)((float)tilemap->parallaxScrollSpeedY/100)) > TheGame::Instance()->getWindowHeight()))
          {

            //calculate the row/col index in the tilemap spritesheet for this current tile  
            int row = tilemap->tileSpriteIndexes[(y*mapSizeX) + (x)]
                % tilemap->spritesheetNumColumns; //modulo the width of the spritesheet to get the left over row index
            int col = (float)tilemap->tileSpriteIndexes[(y*mapSizeX) + (x)]
                / tilemap->spritesheetNumColumns; //divide by width and round down number to get the column index
                
            //call to draw the tile
            TheRenderManager::Instance()->drawTile(tilemap->spritesheetDataFileName, //ID
                                                    ((x * tilemap->tileSizeX) - ((gameObjects[0]->getPosition().getX()) - TheGame::Instance()->getWindowWidth()/2) * (float)((float)tilemap->parallaxScrollSpeedX/100)), //x
                                                    ((y * tilemap->tileSizeY) - (TheCamera::Instance()->getPosition().getY()) * (float)((float)tilemap->parallaxScrollSpeedY/100)),//y
                                                    (int)row, //the row in the spritesheet at which the sprite is
                                                    (int)col, //column in spritesheet
                                                    tilemap->tileSizeX, //width
                                                    tilemap->tileSizeY, //height
                                                    TheGame::Instance()->getRenderer(), //renderer
                                                    SDL_FLIP_NONE);
          }
        }
      }
    }
  }
}
