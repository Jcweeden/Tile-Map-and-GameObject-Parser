#ifndef _LoaderParams_
#define _LoaderParams_
#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "Vector2D.h"
#include <iostream>
#include <string>

/**
  LoaderParams contains all the parameter values for a GameObject. Holding
  all values inside a single class is easier to manage and adjust when put
  to use in different projects, as different objects will require different 
  parameters. 

  I'm not sure I like this approach.
**/
class LoaderParams
{
public:
LoaderParams(int x, int y, int width, int height, std::string textureID, int numFrames, Vector2D startPos = Vector2D(0,0), Vector2D endPos = Vector2D(0,0), int callbackID = 0, int animSpeed = 0)
    : m_x(x),
      m_y(y),
      m_width(width),
      m_height(height),
      m_textureID(textureID),
      m_numFrames(numFrames),
      startPos(startPos),
      endPos(endPos),
      m_callbackID(callbackID),
      m_animSpeed(animSpeed)
      {
      }

  int getX() const {return m_x; }
  int getY() const {return m_y; }
  int getWidth() const {return m_width;}
  int getHeight() const {return m_height;}
  int getNumFrames() const { return m_numFrames; }
  int getAnimSpeed() const { return m_animSpeed; }
  int getCallBackID() const { return m_callbackID; }
  Vector2D getStartPos() const { return startPos; }
  Vector2D getEndPos() const { return endPos; }
  std::string getTextureID() const{return m_textureID;}

  
private:
  //all values are member of the GameObject class

  int m_x;
  int m_y;

  int m_width;
  int m_height;

  int m_numFrames;
  int m_animSpeed;
  int m_callbackID;

  Vector2D startPos;
  Vector2D endPos;
  
  std::string m_textureID;
};


#endif
