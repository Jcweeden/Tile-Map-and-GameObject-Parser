#include "PlayerLevel01.h"

PlayerLevel01::PlayerLevel01() :
    GameObject(), moving(false)
{
  m_currentRow = 3;
}

void PlayerLevel01::draw()
{
  if (moving)
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
  }
  else //if stationary
  {//but if the current row is not set to display movement sprites
    if (m_currentRow != 0 || m_currentRow != 2 ||
        m_currentRow != 4 || m_currentRow != 6)
    {
      switch (m_currentRow)
      {
        case 2:
          m_currentRow = 1;
          break;
        case 4:
          m_currentRow = 3;
          break;
        case 6:
          m_currentRow = 5;
          break;
        case 8:
          m_currentRow = 7;
          break;
      }
    }
  }

  GameObject::draw();
}

void PlayerLevel01::update()
{
  m_velocity.setX(0);
  m_velocity.setY(0);

  handleInput();

  if (m_velocity.getX() != 0 ||
      m_velocity.getY() != 0)
    moving = true;
  else
    moving = false;

  if (moving)
    m_currentFrame = int(((SDL_GetTicks() / 100) % 2));
  else
    m_currentFrame = 0;
  
  GameObject::update();
}

void PlayerLevel01::handleInput()
{
  //KEYBOARD INPUT
  if (TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_RIGHT))
  {
    m_velocity.setX(1);
    moving = true;
  }
  if (TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_LEFT))
  {
    m_velocity.setX(-1);
    moving = true;

  }
  if (TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_UP))
  {
    m_velocity.setY(-1);
    moving = true;

  }
  if (TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_DOWN))
  {
    m_velocity.setY(1);
    moving = true;
  }
  else
  {
    moving = false;
  }
  
}

void PlayerLevel01::load(const LoaderParams *pParams) {
  GameObject::load(pParams);

  TheCamera::Instance()->setTarget(&m_position);
  TheCamera::Instance()->setPosition(m_position);

}
