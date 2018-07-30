#include "GameObjectFactory.h"

GameObjectFactory* GameObjectFactory::s_instance = 0;

GameObjectFactory* GameObjectFactory::Instance()
{
  if (s_instance == 0)
  {
    s_instance = new GameObjectFactory();
  }
  return s_instance;
}

GameObjectFactory::GameObjectFactory() {}


//using ID associated to object type searches to see if the type is already in the map
//if not, add creator object for that class associted with given ID
bool GameObjectFactory::registerType(std::string typeID, BaseCreator* pCreator)
{
  //search though the registered creators and see if the typeID passed in is already in the map
  std::map<std::string, BaseCreator*>::iterator it = m_creators.find(typeID);
  
  //if the type is already registered 
  if (it != m_creators.end())
  {
    //delete passed in pointer and return
    delete pCreator;
    return false;
  }
  //else, add new type to the map
  m_creators[typeID] = pCreator;
  return true;
}


//searches for the parameter ID in the map of registered creators
//if the type is in the map, the Creator for that ID returns a pointer to a new instance of the GameObj it creates
GameObject* GameObjectFactory::create(std::string typeID)
{
  //search though the registered creators and see if the typeID passed in is already in the map
  std::map<std::string, BaseCreator*>::iterator it = m_creators.find(typeID);

  //if reached end of map then the ID has not been registered
  if (it == m_creators.end())
  {
    std::cout << "could not find type: " << typeID << " - ensure RegisterType() has been run for GameObjectFactory Instance\n";
    return NULL;
  }

  //else have the creator return a new instance of the GameObj of the given type
  BaseCreator* pCreator = (*it).second;
  return pCreator->CreateGameObject();
}
