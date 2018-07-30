#ifndef _GameObjectFactory_
#define _GameObjectFactory_


#include <string>
#include <map>
#include <iostream>


class GameObject;

//BaseCreator is a template for all creator classes, ensuring that they implement the CreateGameObject
//method
class BaseCreator
{
public:
  virtual GameObject* CreateGameObject() const = 0;
  virtual ~BaseCreator() {}
};

#include "GameObject.h"


class GameObjectFactory
{
public:
  //GameObjectFactory singleton accessor
  static GameObjectFactory* Instance();

  //searches map of registered creators with the key ID to see if the creator is already in the map
  //if not, adds to the map the Creator class for the object and with its given ID key
  bool registerType(std::string typeID, BaseCreator* pCreator);

  //searches with the parameter ID key in the map of Creator classes
  //if the key is in the map, the Creator for that ID returns a pointer to a new instance of the GameObj it creates
  GameObject* create(std::string typeID);

private:
  
  //constructor
  GameObjectFactory();

  //singleton instance
  static GameObjectFactory* s_instance;

  //map holding string IDs that are the key to Creator classes for a different kind of gameObject
  //for instance, "PLAYER" may be stored as a key for the PlayerCreator class, and upon retrieving
  //the creator class CreateGameObject() can be called to return a pointer to a new instance of
  //that class
  std::map<std::string, BaseCreator*> m_creators;

  //static GameObjectFactory* pInstance;
};

typedef GameObjectFactory TheGameObjectFactory;

#endif
