#ifndef _EnemyLevel01_
#define _EnemyLevel01_
#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"

#include "../GameObject.h"
#include "../GameObjectFactory.h"
#include "../LoaderParams.h"

#include <iostream>

class EnemyLevel01 : public GameObject
{
public:
  EnemyLevel01();
  
  void draw();
  void update();

  void load(const LoaderParams *pParams);

public:

  int movementDir;

  Vector2D startPos;
  Vector2D endPos;
};

//Creator implementation that allows for creation of objects in the GameObjectFactory
class EnemyLevel01Creator : public BaseCreator
{
  GameObject* CreateGameObject() const
  {
    return new EnemyLevel01();
  }
};

#endif
