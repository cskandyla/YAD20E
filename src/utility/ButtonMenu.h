#include <SDL2/SDL.h>
#include <vector>
#include "Button.h"




#ifndef _M_BUTTONMENU__
#define _M_BUTTONMENU__


//ON ADD CHECK FOR BACKGROUND AND SET IT
enum Orientation{O_DOWN,O_RIGHT};

class ButtonMenu
{
 private:
  vector<Button*> buttons;
  SDL_Texture *background;
  Orientation orient;
  SDL_Rect starting_pos;
  bool visible;
  
 public:
  ButtonMenu(Orientation orient,SDL_Rect starting_pos);
  virtual ~ButtonMenu();
  void Add(string name,string image);
  void Add(string name,string image,void (*ButtonAction)(void*),void *data);
  void Add(string name,SDL_Texture *surf);
  void Add(Button *button);
  void Remove(Button *button);
  void Clear();
  void Draw(SDL_Texture *screen);
  Button* Clicked(int x,int y);
  void Show(bool visible);
  bool Shown();
  void SetBackground(string backgroundimage);
  void SetBackground(SDL_Texture * background);
  int size();

  vector<Button*>& GetButtons();
    

};

#endif
