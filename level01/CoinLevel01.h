#ifndef _CoinLevel01_
#define _CoinLevel01_
#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"

#include "../GameObject.h"

#include "../InputHandler.h"
#include "../GameObjectFactory.h"
#include "../LoaderParams.h"

#include <iostream>

class CoinLevel01 : public GameObject
{
public:
  CoinLevel01();
  
  void draw();
  void update();

  void load(const LoaderParams *pParams);


  //private:
  //void handleInput();
};

//Creator implementation that allows for creation of objects in the GameObjectFactory
class CoinLevel01Creator : public BaseCreator
{
  GameObject* CreateGameObject() const
  {
    return new CoinLevel01();
  }
};

#endif
