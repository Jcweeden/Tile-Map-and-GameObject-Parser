#include "EnemyLevel01.h"

EnemyLevel01::EnemyLevel01() :
    GameObject()
{
 
}

void EnemyLevel01::draw()
{

  if(m_velocity.getX() < 0) {
    m_currentRow = 8;
  }
  else if(m_velocity.getX() > 0) {
    m_currentRow = 6;
  }
  else if(m_velocity.getY() < 0) {
    m_currentRow = 4;
  }
  else if(m_velocity.getY() > 0) {
    m_currentRow = 2;
  }
  

  GameObject::draw();
}

void EnemyLevel01::update()
{
  
  if (movementDir == 0) //move on x axis
  {
    if(m_position.getX() < startPos.getX())
    {
      m_velocity.setX(1);
    }
    else if (m_position.getX() > endPos.getX())
    {
      m_velocity.setX(-1);
    }
  }
  else if (movementDir == 1)
  {
    if(m_position.getY() < startPos.getY())
    {
      m_velocity.setY(1);
    }
    else if (m_position.getY() > endPos.getY())
    {
      m_velocity.setY(-1);
    }
  }

  m_currentFrame = int(((SDL_GetTicks() / 100) % 2));
  
  GameObject::update();
}

void EnemyLevel01::load(const LoaderParams *pParams) {
  GameObject::load(pParams);

  //load in movement positions
  startPos = pParams->getStartPos();
  endPos = pParams->getEndPos();

  Vector2D diff = endPos - startPos;

  if (diff.getX() > 0)
  {
    movementDir = 0;
  }
  else
    movementDir = 1;

  //std::cout << movementDir << "\n";

}
