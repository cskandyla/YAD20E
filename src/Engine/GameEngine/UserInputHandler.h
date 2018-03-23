#include <SDL2/SDL.h>
#include <utility>
#include "InputState.h"
using std::pair;

#ifndef __USERINPUTHANDLER_H_
#define __USERINPUTHANDLER_H_
class Camera;
class CellInfo;
class Turn;



class UserInputHandler
{
 private:
  Camera *camera;
  Turn *the_turn;
  InputState *i_state;

 public:
  //Constructor/Initialization 
  UserInputHandler(Camera *camera,Turn *the_turn);
  virtual ~UserInputHandler();
  // Event Handlers
  void HandleEvents(SDL_Event *event);
  //LeftClick and LeftClick handlers
  void LeftClick(SDL_Event *event);
  void ClickedOnCharacter(CellInfo *cellinfo);
  void ClickedOnEmptySpace(SDL_Rect cellrect);
  void ClickedOnObject(CellInfo *cellinfo);
  //RightClick and RightClick handlers    
  void RightClick(SDL_Event *event);
  void SetState(InputState *i_state);
  InputState* GetState();
  
};


#endif
