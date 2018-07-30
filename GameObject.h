#ifndef _GameObject_
#define _GameObject_
#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "LoaderParams.h"
#include "Camera.h"
//#include "Game.h"
#include <string>

class GameObject {

public:
  GameObject();

  virtual void draw();
  virtual void update();
  virtual void clean();

  //objects are created via a load function so that objects can be instantiated via
  //creator classes deriving the class data from an external XML file
  virtual void load(const LoaderParams *pParams);
  
  Vector2D& getPosition() { return m_position; }
  Vector2D& getVelocity() { return m_velocity; }

  int getWidth() { return m_width; }
  int getHeight() { return m_height; }
  
protected:
  Vector2D m_position;
  Vector2D m_velocity;
  Vector2D m_acceleration;
  
  int m_width;
  int m_height;

  //if the gameObj has an animated sprite, these integers indicate the index of the current sprite in the sprite sheet
  int m_currentRow;
  int m_currentFrame;

  int m_callbackID;
  
  //stringID that will return the texture associated with the gameObject in RenderManager
  std::string m_textureID;
};

#endif
