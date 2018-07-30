#include "GameObject.h"
#include "Game.h"

GameObject::GameObject() :
    m_position(0, 0), m_velocity(0,0), m_acceleration(0,0)
{

}

void GameObject::draw() {
  RenderManager::Instance()->drawFrame(m_textureID, (int)m_position.getX() - TheCamera::Instance()->getPosition().getX(), (int)m_position.getY() - TheCamera::Instance()->getPosition().getY(), m_width, m_height, m_currentRow, m_currentFrame, TheGame::Instance()->getRenderer());
  
}

void GameObject::update(){
  //apply physics
  m_velocity += m_acceleration;
  m_position += m_velocity;
};

void GameObject::clean(){

};

void GameObject::load(const LoaderParams *pParams)
{
  m_position = Vector2D(pParams->getX(), pParams->getY());
  m_velocity = Vector2D(0,0);
  m_acceleration = Vector2D(0,0);
  
  m_width =  pParams->getWidth();
  m_height =  pParams->getHeight();
  
  m_textureID = pParams->getTextureID();

  m_currentRow = 1;
  m_currentFrame = 1;
}
