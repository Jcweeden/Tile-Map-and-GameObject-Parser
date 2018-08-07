#include "Game.h"
#include "Level.h"
#include <iostream>
#include "level01/PlayerLevel01.h"
#include "level01/EnemyLevel01.h"
#include "level01/CoinLevel01.h"

//define static instance
Game* Game::s_pInstance = 0;

bool Game::init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen)
{
  int flags = 0;

  if (fullscreen) {//if method parameter = true then make variable in line below
    flags = SDL_WINDOW_SHOWN;
  }
  
  // initialise SDL
   if(SDL_Init(SDL_INIT_EVERYTHING) == 0)
   {
     std::cout << "Game: SDL init success\n";
     // if succeeded create our window
     m_pWindow = SDL_CreateWindow(title, xpos, ypos, width, height, flags);
 
 // if the window creation succeeded create our renderer
     if(m_pWindow != 0)
     {
       std::cout << "Game: Window creation success\n";
       m_pRenderer = SDL_CreateRenderer(m_pWindow, -1, 0);

       if (m_pRenderer != 0) {
         std::cout << "Game: Renderer creation success\n";
         SDL_SetRenderDrawColor(m_pRenderer, 255, 255, 255, 255);
       }
       else {
         std::cout << "Game: Renderer init failed\n";
         return false;
       }
     }
     else
     {
       std::cout << "Game: Window init failed\n";
       return false;
     }
   }
   else
   {
     std::cout << "Game: SDL init failed\n";
     return false; // sdl could not initialise
   }

   std::cout << "Game: Init success\n";
   m_bRunning = true;//start the main loop


   //loadTextures();

   //TheInputHandler::Instance()->initialiseJoysticks();

   //load creators into GameObjectFactory
   //GameObjectFactory::Instance()->registerType("MenuButton", new MenuButtonCreator());

   GameObjectFactory::Instance()->registerType("PlayerLevel01", new PlayerLevel01Creator());
   GameObjectFactory::Instance()->registerType("EnemyLevel01", new EnemyLevel01Creator());
   GameObjectFactory::Instance()->registerType("CoinLevel01", new CoinLevel01Creator());

   // m_pGameStateMachine = new GameStateMachine();
   
   //start on MenuState
   //m_pGameStateMachine->changeState(new MainMenuState());

   level = new Level();
   
   level->setupLevel(
       "///Users/Joshua/Documents/GameDev/Emacs/Tile-Map-and-GameObject-Parser/data/level01Tiles.xml",
       "///Users/Joshua/Documents/GameDev/Emacs/Tile-Map-and-GameObject-Parser/data/level01GameObjects.xml");
   
   return true;
}

//put textures in memory
void Game::loadTextures() {

}

void Game::render()
{
  SDL_RenderClear(m_pRenderer); // clear the renderer to the draw colour

  // m_pGameStateMachine->render();
  level->draw();
  
  SDL_RenderPresent(m_pRenderer);  //draw to the screen
}

void Game::update() {

  //m_pGameStateMachine->update();
  level->update();
}

void Game::clean() {
  std::cout << "Game: cleaning game\n";

  level->clean();
  
  TheInputHandler::Instance()->clean(); //remove any controller connections
  
  SDL_DestroyWindow (m_pWindow);
  SDL_DestroyRenderer (m_pRenderer);
  std::cout << "Game: SDL_Quit()\n\n";
  SDL_Quit();
}

void Game::handleEvents()
{
  TheInputHandler::Instance()->update();

  /*
  if (TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_RETURN))
  {
    m_pGameStateMachine->changeState(new PlayState());
  }
  */
}

void Game::quit() {
  m_bRunning = false;
}
