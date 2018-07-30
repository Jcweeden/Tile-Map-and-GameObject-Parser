#ifndef _InputHandler_
#define _InputHandler_
#include "SDL2/SDL.h"
#include "Vector2D.h"
#include <iostream>
#include <vector> 

enum mouse_buttons
{
  LEFT = 0,
  MIDDLE = 1,
  RIGHT = 2
};


class InputHandler {
public:
  //returns / creates singleton Instance
  static InputHandler* Instance();

  InputHandler(); //constructor
  ~InputHandler() {} //destructor

  //updates to show any new buttton presses
  void update();

  //clears any initialized joysticks
  void clean(); 

  //uses event to determine the controller input
  void updateJoystickInput(SDL_Event event);

  //true if any joysticks are init
  bool m_bJoysticksInitialised;

  //check for any plugged in joysticks, and inits them
  void initialiseJoysticks();

  //returns true if at least one joystick has been init
  bool joysticksInitialised() { return m_bJoysticksInitialised; }
 
  //returns the position in x and y axis for the left (stick = 1) and right (stick = 2) analogue stick
  //joy is ID of stick we want to use, 1 for left, 2 for right
  int yValue(int joy, int stick);
  int xValue(int joy, int stick);

  //returns whether controller and button number is being pressed
  bool getButtonState(int joy, int buttonNumber) { return m_buttonStates[joy][buttonNumber]; }

  //returns whether a button is being pressed or not
  bool getMouseButtonState(int buttonNumber) { return m_mouseButtonStates[buttonNumber]; }

  //returns coords of the mouse's last positon on screen
  Vector2D* getMousePosition() { return m_mousePosition; }

  //returns true if parameter key is pressed
  bool isKeyDown(SDL_Scancode key);

  //resets mouse button presses
  void reset();
  
private:

  //static instance of TheInputHandler
  static InputHandler* s_pInstance;

  //vector storing all init joysticks
  //pointers are last used to close connections to the joysticks in clean()
  std::vector<SDL_Joystick*> m_joysticks;

  //deadzone val determining a threshold that must be passed for a joystick analouge stick movement to be registered
  const int m_joystickDeadzone = 10000;
  
  std::vector<std::pair<Vector2D*, Vector2D*> > m_joystickValues;
  //pair, one for each stick - Vector2D will contains movements of stick

  //a list of buttons for each controller, true if pressed
  std::vector<std::vector<bool> > m_buttonStates;

  //holds three bool values for each mouse button, true is button is clicked
  std::vector<bool> m_mouseButtonStates;

  //updated to hold the current position of the mouse on screen
  Vector2D* m_mousePosition;

  //arrray holding a bool value for each key on the keyboard, true if key is pressed
  const Uint8* m_keystates;
};

typedef InputHandler TheInputHandler;

#endif
