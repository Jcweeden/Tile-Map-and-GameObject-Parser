#ifndef _Camera_
#define _Camera_

#include "Vector2D.h"
#include "Game.h"

#include <iostream>

class Camera
{
public:

  //create/return static singleton
  static Camera* Instance();

  //sets the target GameObject that the camera will track the position of (currently set to Player in Player.cpp)
  void setTarget(Vector2D* target) { targetPosition = target; }

  //sets the position of the camera to given vector
  void setPosition(const Vector2D& p_position) { position = p_position; }

  //returns the position of the camera
  //should it be outside the edge of the map boudaries, the returned val is clamped to the edge
  Vector2D getPosition();

  //returns the position of the object the camera is following (e.g. the player)
  Vector2D getTargetPosition();

  //when the XML is parsed, the size of the map is saved within the camera class
  void setMapWidth(int val) { mapWidth = val; }
  void setMapHeight(int val) { mapHeight = val; }

public:
  Camera();  //constructor
  ~Camera(); //destructor

  //current position of the target the camera is following
  Vector2D* targetPosition;
  //current position of the camera
  Vector2D position;

  //pixel w/h of the entire tilemap
  int mapWidth;
  int mapHeight;

  //singleton instance
  static Camera* s_pCamera;
};

typedef Camera TheCamera;

#endif
