#include "InputHandler.h"
#include "Game.h"


//define static instance
InputHandler* InputHandler::s_pInstance = 0;

InputHandler* InputHandler::Instance()
  {
    if(s_pInstance ==0)
    {
      s_pInstance = new InputHandler();
    }
    return s_pInstance;
  }

InputHandler::InputHandler() 
: m_mousePosition(new Vector2D(0,0))
{
  //MOUSE setup - define vector that stores current state of each mouse button
  for (size_t i = 0; i < 3; i++)
  {
    m_mouseButtonStates.push_back(false);
  }
    //m_mousePosition = new Vector2D(0,0);
}


void InputHandler::initialiseJoysticks(){
  if (SDL_WasInit(SDL_INIT_JOYSTICK) == 0) //check if joystick system has been init
  {
    SDL_InitSubSystem(SDL_INIT_JOYSTICK); //if not then init it
  }

  if (SDL_NumJoysticks() > 0) //check if any joysticks are available
  {
    for (int i = 0; i < SDL_NumJoysticks(); i++) //loop through all available joysticks
    {
      SDL_Joystick* joy = SDL_JoystickOpen(i); //open the joystick
      
      if (joy) //if joystick is there to be opened
      {
        m_joysticks.push_back(joy); //add to array so can be closed later

        //pair, one for each stick
        m_joystickValues.push_back(std::make_pair(new Vector2D(0,0), new Vector2D(0,0)));
      }
      else
      {
        std::cout << SDL_GetError();
      }
    }
    SDL_JoystickEventState(SDL_ENABLE); //start listening for joystick events
    m_bJoysticksInitialised = true;

    std::cout << "InputHandler: Init " << m_joysticks.size() << " joystick(s)\n";
  }
  else
  {
    m_bJoysticksInitialised = false;
    
    std::cout << "InputHandler: Joysticks not found\n";
  }

  //JOYSTICK BUTTONS
  for(int i = 0; i < SDL_NumJoysticks(); i++)
  {
    SDL_Joystick* joy = SDL_JoystickOpen(i);
    if(joy)
    {
      m_joysticks.push_back(joy);
      m_joystickValues.push_back(std::make_pair(new Vector2D(0,0), new Vector2D(0,0)));

      std::vector<bool> tempButtons;

      for (int j = 0; j < SDL_JoystickNumButtons(joy); j++) //get number of buttons on the joystick
      {
        tempButtons.push_back(false); //start at false to indicate the button is not being pressed
      }

      m_buttonStates.push_back(tempButtons);
    }
  }
}

void InputHandler::clean()
{
  //if joysticks have been init
  if (m_bJoysticksInitialised) 
  {
    //for each joystick
    for (unsigned int i = 0; i < SDL_NumJoysticks(); i++) { 
      SDL_JoystickClose(m_joysticks[i]); //close the connection
    }
    std::cout << "InputHandler: Joysticks connection closed\n";
  }
}

//called each frame to update event states
void InputHandler::update()
{
  SDL_Event event; //get the event for current frame

  //should there be an action in this frame
  while(SDL_PollEvent(&event))
  {
    //update the presssed keys
    m_keystates = SDL_GetKeyboardState(0);

    //QUIT
    if (event.type == SDL_QUIT)
    {
      std::cout << "InputHandler: Quit event\n";
      TheGame::Instance()->quit();
    }

    //JOYSTICK
    if (m_bJoysticksInitialised)
    {
      updateJoystickInput(event);
    }
    
    //MOUSE BUTTONS
    if(event.type == SDL_MOUSEBUTTONDOWN)
    {
      if (event.button.button == SDL_BUTTON_LEFT)
      {
        m_mouseButtonStates[LEFT] = true;
        
      }
      if (event.button.button == SDL_BUTTON_MIDDLE)
      {
        m_mouseButtonStates[MIDDLE] = true;
      }
      if (event.button.button == SDL_BUTTON_RIGHT)
      {
        m_mouseButtonStates[RIGHT] = true;
      } 
    }
    if (event.type == SDL_MOUSEBUTTONUP)
    {
      if (event.button.button == SDL_BUTTON_LEFT)
      {
        m_mouseButtonStates[LEFT] = false;
      }
      if (event.button.button == SDL_BUTTON_MIDDLE)
      {
        m_mouseButtonStates[MIDDLE] = false;
      }
      if (event.button.button == SDL_BUTTON_RIGHT)
      {
        m_mouseButtonStates[RIGHT] = false;
      }
    }

    //MOUSE MOTION
    if(event.type == SDL_MOUSEMOTION)
    {
      // std::cout << "InputHandler::update: button motion x: " << event.motion.x << " y: " << event.motion.y << std::endl;
      m_mousePosition->setX((float)event.motion.x);
      m_mousePosition->setY((float)event.motion.y);
    }
  }
}



//returns true if passed in key is down
bool InputHandler::isKeyDown(SDL_Scancode key)
{
  if (m_keystates != 0)
  {
    if (m_keystates[key] == 1) {
      return true;
    }
    else
    {
      return false;
    }
  }
  return false;
}


int InputHandler::xValue(int joy, int stick)
{
  if (m_joystickValues.size() > 0) {
    if (stick == 1)
    {
      return m_joystickValues[joy].first->getX();
    }
    else if (stick == 2)
    {
      return m_joystickValues[joy].second->getX();
    }
  }
  return 0;
}

int InputHandler::yValue(int joy, int stick)
{
   if (m_joystickValues.size() > 0) {
    if (stick == 1)
    {
      return m_joystickValues[joy].first->getY();
    }
    else if (stick == 2)
    {
      return m_joystickValues[joy].second->getY();
    }
  }
  return 0;
}


void InputHandler::updateJoystickInput(SDL_Event event)
{
  if(event.type == SDL_JOYAXISMOTION)
  {
    int whichOne = event.jaxis.which; //get which controller event came from

    //LEFT STICK
    //left stick move left or right
    if (event.jaxis.axis == 0)
    {
      if (event.jaxis.value > m_joystickDeadzone)
      {
        m_joystickValues[whichOne].first->setX(1);
      }
      else if(event.jaxis.value < -m_joystickDeadzone)
      {
        m_joystickValues[whichOne].first->setX(-1);
      }
      else
      {
        m_joystickValues[whichOne].first->setX(0);
      }
    }

    //left stick move up or down
    if (event.jaxis.axis == 1)
    {
      if (event.jaxis.value > m_joystickDeadzone)
      {
        m_joystickValues[whichOne].first->setY(1);
      }
      else if(event.jaxis.value < -m_joystickDeadzone)
      {
        m_joystickValues[whichOne].first->setY(-1);
      }
      else
      {
        m_joystickValues[whichOne].first->setY(0);
      }
    }

    //RIGHT STICK
    //right stick move left or right
    if (event.jaxis.axis == 3)
    {
      if (event.jaxis.value > m_joystickDeadzone)
      {
        m_joystickValues[whichOne].second->setX(1);
      }
      else if(event.jaxis.value < -m_joystickDeadzone)
      {
        m_joystickValues[whichOne].second->setX(-1);
      }
      else
      {
        m_joystickValues[whichOne].second->setX(0);
      }
    }
        
    //right stick move up or down
    if (event.jaxis.axis == 4)
    {
      if (event.jaxis.value > m_joystickDeadzone)
      {
        m_joystickValues[whichOne].second->setY(1);
      }
      else if(event.jaxis.value < -m_joystickDeadzone)
      {
        m_joystickValues[whichOne].second->setY(-1);
      }
      else
      {
        m_joystickValues[whichOne].second->setY(0);
      }
    }
  }//endifJOYSTICKAXISMOTION
    
  //BUTTONS
  if(event.type == SDL_JOYBUTTONDOWN)
  {
    int whichOne = event.jaxis.which;
      
    //set the pressed controller, button to true
    m_buttonStates[whichOne] [event.jbutton.button] = true;
  }
  if(event.type == SDL_JOYBUTTONUP)
  {
    int whichOne = event.jaxis.which;

    m_buttonStates[whichOne] [event.jbutton.button] = false;
  }
   
}

void InputHandler::reset()
{
  m_mouseButtonStates[LEFT] = false;
  m_mouseButtonStates[MIDDLE] = false;
  m_mouseButtonStates[RIGHT] = false;
}
