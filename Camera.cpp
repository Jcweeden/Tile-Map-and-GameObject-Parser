#include "Camera.h"

Camera* Camera::s_pCamera = new Camera();

Camera::Camera()
    : targetPosition(0), position(0,0)
{}

Camera::~Camera()
{
  delete targetPosition;
}

Camera* Camera::Instance()
{
  if(s_pCamera == 0)
  {
    s_pCamera = new Camera();
  }
  return s_pCamera;
}

Vector2D Camera::getPosition()
{
  
  //if the camera has a target
  if(targetPosition != 0)
  {
    //set the camera position to 
    Vector2D pos(targetPosition->getX() - (TheGame::Instance()->getWindowWidth() / 2),
                 targetPosition->getY() - (TheGame::Instance()->getWindowHeight() / 2));


    //if below the lower x boundary
    if (pos.getX() < 0)
    {
      //clamp the camera to the edge
      pos.setX(0);
      //std::cout << "less than 0 - getPosition\n";
    }
    //else if above the upper y boundary
    else if (pos.getX() > mapWidth - (TheGame::Instance()->getWindowWidth()))
    {
      //clamp the camera to the edge
      pos.setX(mapWidth - (TheGame::Instance()->getWindowWidth()));
      //std::cout << "more than edge - getPosition: " << pos.getX() << " > " << mapWidth
      //        << " - "  << TheGame::Instance()->getWindowWidth() << "\n";
    }
    
    //if below the lower y boundary
    if (pos.getY() < 0)
    {
      //clamp the camera to the edge
      pos.setY(0);
      //std::cout << "less than 0 - getPosition\n";
    }
    //else if above the upper y boundary
    else if (pos.getY() > mapHeight - (TheGame::Instance()->getWindowHeight()))
    {
      //clamp the camera to the edge
      pos.setY(mapHeight - (TheGame::Instance()->getWindowHeight()));
      //std::cout << "more than edge - getPosition\n";
    }
    
    return pos;
  }
    
  return position;
}

Vector2D Camera::getTargetPosition()
{
  return *targetPosition;
}
  
