#include "CoinLevel01.h"

CoinLevel01::CoinLevel01() :
    GameObject()
{

}

void CoinLevel01::draw()
{
  GameObject::draw();
}

void CoinLevel01::update()
{
  m_currentFrame = int(((SDL_GetTicks() / 100) % 8));
  
  GameObject::update();
}

//void PlayerLevel01::clean(){}

//void CoinLevel01::handleInput()
//{
//}

void CoinLevel01::load(const LoaderParams *pParams) {
  GameObject::load(pParams);
}
