#ifndef _Game_
#define _Game_
#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"


#include "InputHandler.h"
#include "RenderManager.h"
#include "GameObject.h"
#include "LoaderParams.h"

//#include "Level.h"

#include <vector>

class Level;
class GameObject;

class Game {

public:

    static Game* Instance()
  {
    if(s_pInstance == 0)
    {
      s_pInstance = new Game();
      return s_pInstance;
    }
    return s_pInstance;
  }

  ~Game() {}

  // simply sets the running variable to true
  bool init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen);
  void render();
  void update();
  void handleEvents();
  void clean();
  void quit();

  void loadTextures();//remove
  
  //a function to access the private variable that is true when the program is running
  bool running() {return m_bRunning;}
  
  std::vector<GameObject*> m_gameObjects;

  //function to return the renderer
  SDL_Renderer* getRenderer() const { return m_pRenderer; }

  //function to return the stateMachine
  //GameStateMachine* getStateMachine(){return m_pGameStateMachine; }

  //returns the size of the screen, as defined in main.cpp
  int getWindowWidth() {return screenWidth; }
  int getWindowHeight() {return screenHeight; }

  void setWindowWidth(int val) {screenWidth = val; }
  void setWindowHeight(int val) {screenHeight = val; }


public:

    Level* level;

private:

  Game() {}


  //static instance variable
  static Game* s_pInstance;
  
  SDL_Window* m_pWindow;
  SDL_Renderer* m_pRenderer;

  // GameStateMachine* m_pGameStateMachine;
    
  bool m_bRunning;

  int screenWidth, screenHeight;
};

typedef Game TheGame;

#endif
