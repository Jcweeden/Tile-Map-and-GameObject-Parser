#include <string>
#include "RenderManager.h"

//define static instance
RenderManager* RenderManager::s_pInstance = 0;

RenderManager* RenderManager::Instance()
{
  if(s_pInstance == 0)
  {
    s_pInstance = new RenderManager();
    return s_pInstance;
  }
  return s_pInstance;
}

// from calling this function we will have SDL_Texture within m_textureMap that we can access using its ID
bool RenderManager::load(std::string fileName, std::string id, SDL_Renderer* pRenderer) {
  SDL_Surface* pTempSurface = IMG_Load(fileName.c_str());

  if (pTempSurface == 0) {
    std::cout << "Error in RenderManager::load(): 'pTempSurface == 0'" << std::endl;
    return false;
  }
  
  SDL_Texture* pTexture = SDL_CreateTextureFromSurface(pRenderer, pTempSurface);

  SDL_FreeSurface(pTempSurface);

  if(pTexture !=0)   //if everything went okay, add to our list
  {
    m_textureMap[id] = pTexture;
    return true;
  }
  
  std::cout << "Error in RenderManager::load()" << std::endl;
  return false;   //reaching here meant something went wrong
}

// use passed in ID to get the SDL_Texture we want to draw.
// build our own source and destination variables using the passed in x,y, width,height variables
void RenderManager::draw(std::string id, int x, int y, int width, int height, SDL_Renderer* pRenderer, SDL_RendererFlip flip){

  SDL_Rect srcRect;
  SDL_Rect destRect;

  srcRect.x = 0;
  srcRect.y = 0;
  srcRect.w = destRect.w = width;
  srcRect.h = destRect.h = height;
  destRect.x = x;
  destRect.y = y;

  SDL_RenderCopyEx(pRenderer, m_textureMap[id], &srcRect, &destRect, 0, 0, flip);
}

// create a source rectangle to use appropriate frame of animation using currentFrame and currentRow variables
// source rect's x pos for the frame is the width of the source rect multipled by current frame
// source rect's y pos is the height of the rectangle multipled by currentRow-1
void RenderManager::drawFrame(std::string id, int x, int y, int width, int height, int currentRow, int currentFrame, SDL_Renderer* pRenderer, SDL_RendererFlip flip) {
  
  SDL_Rect srcRect;
  SDL_Rect destRect;
  //std::cout << currentFrame<< std::endl;
  srcRect.x = width * currentFrame;
  srcRect.y = height * (currentRow - 1);
  srcRect.w = destRect.w = width;
  srcRect.h = destRect.h = height;
  destRect.x = x;
  destRect.y = y;

  SDL_RenderCopyEx(pRenderer, m_textureMap[id], &srcRect, &destRect, 0, 0, flip);
}

void RenderManager::drawTile(std::string id, int x, int y, int row, int column, int width, int height, SDL_Renderer* pRenderer, SDL_RendererFlip flip){

  SDL_Rect srcRect;
  SDL_Rect destRect;

  srcRect.x = row * width;
  srcRect.y = column * height;
  srcRect.w = destRect.w = width;
  srcRect.h = destRect.h = height;
  destRect.x = x;
  destRect.y = y;

  SDL_RenderCopyEx(pRenderer, m_textureMap[id], &srcRect, &destRect, 0, 0, flip);
}

//ckears the given texture from the map so it cannot be used again
void RenderManager::clearFromTextureMap(std::string id)
{
  m_textureMap.erase(id);
}
