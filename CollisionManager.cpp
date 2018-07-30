#include "CollisionManager.h"

#include <iostream>


CollisionManager* CollisionManager::s_pInstance = 0;

CollisionManager* CollisionManager::Instance()
  {
    if(s_pInstance == 0)
    {
      s_pInstance = new CollisionManager();
      return s_pInstance;
    }

    return s_pInstance;
  }

double CollisionManager::clamp(double value, double upper, double lower)
{
  return std::min(upper, std::max(value, lower));
}

bool CollisionManager::isCollidingRectRect(GameObject* rectA, GameObject* rectB, int buffer)
{
  //calculate buffers that reduce the hitbox size of the rects
  int aHBuf = rectA->getHeight() / buffer;
  int aWBuf = rectA->getWidth() / buffer;
    
  int bHBuf = rectB->getHeight() / buffer;
  int bWBuf = rectB->getWidth() / buffer;
  
  //if the bottom of rectA is lower than the top of rectB - no collision
  if((rectA->getPosition().getY() + rectA->getHeight()) - aHBuf <= rectB->getPosition().getY() + bHBuf)
  { return false; }
    
  //if the top of rectA is higher than the bottom of rectB - no collision
  if(rectA->getPosition().getY() + aHBuf >= (rectB->getPosition().getY() + rectB->getHeight()) - bHBuf)
  { return false; }
    
  //if the right of rectA does not meet the left of rectB - no collision
  if((rectA->getPosition().getX() + rectA->getWidth()) - aWBuf <= rectB->getPosition().getX() +  bWBuf)
  { return false; }
    
  //if the left of rectA is further away than the right of rectB - no collision
  if(rectA->getPosition().getX() + aWBuf >= (rectB->getPosition().getX() + rectB->getWidth()) - bWBuf)
  { return false; }
    
  //else, a collision
  return true;
}


bool CollisionManager::isCollidingRectCircle(GameObject* circle, GameObject* rect)
{
  //find the closest point to the circle within the rect
  float closestX = clamp(circle->getPosition().getX(),
                         rect->getPosition().getX(),
                         rect->getPosition().getX() + rect->getWidth());
  
  float closestY = clamp(circle->getPosition().getY(),
                         rect->getPosition().getY(),
                         rect->getPosition().getY() + rect->getHeight());

  //calc distance between the circle's center and this closest point
  float distanceX = circle->getPosition().getX() - closestX;
  float distanceY = circle->getPosition().getY() - closestY;

  //if dist is less than the circle's radius, is a collision
  float distanceSquared = (distanceX * distanceX) + (distanceY * distanceY);
  return distanceSquared < (circle->getWidth()/2 * circle->getWidth()/2);
}


bool CollisionManager::isCollidingCircleCircle(GameObject* circleA, GameObject* circleB)
{
  //sqrt(sqr(x)+sqr(y))
  
  float dx = circleB->getPosition().getX() - circleA->getPosition().getX();
  float dy = circleB->getPosition().getY() - circleA->getPosition().getY();
  float radii = circleB->getWidth()/2 + circleA->getWidth()/2;

  //if distance between origins of 2 circles is smaller than their combined radii 
  if ( ( dx * dx )  + ( dy * dy ) < radii * radii )   {
    //the circles are colliding
    return true;
  }
  else
  {
    return false;
  }
}

bool CollisionManager::isCollidingCirclePoint(GameObject* circleA, Vector2D* pointPosition)
{    //formula: sqrt(sqr(x)+sqr(y))

  float dx = pointPosition->getX() - circleA->getPosition().getX();
  float dy = pointPosition->getY() - circleA->getPosition().getY();
  float radii = 1 + circleA->getWidth()/2;

  //if distance between origins of circle and point is smaller than their combined radii 
  if ( ( dx * dx )  + ( dy * dy ) < radii * radii )   {
    //the circle and point are colliding
    return true;
  }
  else
  {
    return false;
  }
}




