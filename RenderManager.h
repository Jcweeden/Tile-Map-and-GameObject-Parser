#ifndef _RenderManager_
#define _RenderManager_
#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include <iostream>
#include <map>

class RenderManager {

public:

  //define static instance if one does not exist, or return the existing instance
  static RenderManager* Instance();
  
  //loads a file into m_textureMap with the ID being its accessor key
  bool load(std::string fileName, std::string id, SDL_Renderer* pRenderer);

  //draws a static image
  void draw(std::string id, int x, int y, int width, int height, SDL_Renderer* pRenderer, SDL_RendererFlip flip = SDL_FLIP_NONE);
  
  //draws the given coords of a spritesheet according to a frame and row of the spritesheet
  void drawFrame(std::string id, int x, int y, int width, int height, int currentRow, int currentFrame, SDL_Renderer* pRenderer, SDL_RendererFlip flip = SDL_FLIP_NONE);

  void drawTile(std::string id, int x, int y, int row, int column, int width, int height, SDL_Renderer* pRenderer, SDL_RendererFlip flip = SDL_FLIP_NONE);

  //using ID removes texture from current state, not the entire textureMap
  void clearFromTextureMap(std::string id);

private:

  //private constructor for singleton - can only be created by Instance() function
  RenderManager () {};

  //singleton instance of TheRenderManager
  static RenderManager* s_pInstance;

public:
  //map of pointers to SDL_Texture objects, keyed using strings
  std::map<std::string, SDL_Texture*> m_textureMap;
};

typedef RenderManager TheRenderManager;

#endif
