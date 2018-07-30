#ifndef _PlayerLevel01_
#define _PlayerLevel01_
#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"

#include "../GameObject.h"
#include "../InputHandler.h"
#include "../GameObjectFactory.h"
#include "../LoaderParams.h"
#include "../Camera.h"

#include <iostream>

class PlayerLevel01 : public GameObject
{
public:
  PlayerLevel01();
  
  void draw();
  void update();

  void load(const LoaderParams *pParams);


private:
  void handleInput();

public:
  bool moving;
};

//Creator implementation that allows for creation of objects in the GameObjectFactory
class PlayerLevel01Creator : public BaseCreator
{
  GameObject* CreateGameObject() const
  {
    return new PlayerLevel01();
  }
};

#endif
