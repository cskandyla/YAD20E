#include <SDL2/SDL.h>
#include <string>
#include <vector>
#include <utility>
#include "miscellaneous.h"
using std::pair;
using std::string;
using std::vector;

#ifndef _M_BUTTON__
#define _M_BUTTON__

class Button
{

 private:
  string name;
  pair<SDL_Rect,SDL_Texture*>  button_inner;
  SDL_Texture *background;
  //Void* Pointer to pass whatever arguements are neccessary
  void (*ButtonAction)(void* data);
  void *data;
  bool clicked;
  bool visible;
  bool bgdealloc,dealloc;
 public:
  Button(string name,SDL_Rect pos,string image);
  Button(string name,SDL_Rect pos,string image,void (*ButtonAction)(void*),void *data);
  Button(string name,SDL_Rect pos,SDL_Texture *surf);
  virtual ~Button();
  
  void Show(bool flag);
  void Draw(SDL_Texture *screen);
  void SetAction(void (*ButtonAction)(void*),void *data);
  bool Clicked(int x,int y);
  bool WasClicked();
  void SetBackground(SDL_Texture *background);
  void SetBackground(string backgroundimage);
  virtual void Activate();
  SDL_Rect GetRect();
  void SetPosition(int x,int y);
  string GetName();
  SDL_Texture* GetImage();
  

};


#endif
