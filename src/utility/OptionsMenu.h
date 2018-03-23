#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <vector>
#include <string>
using std::vector;
using std::string;
using std::pair;

#ifndef __OPTIONSMENU_H_
#define __OPTIONSMENU_H_

class OptionsMenu
{
  SDL_Surface *button;
  SDL_Surface *button_pressed;
  vector<string> optionstext;
  vector<pair<SDL_Rect,SDL_Surface*> >options;
  TTF_Font *font;
  int max_width;
  SDL_Color textcolor;
  SDL_Rect position;
  bool Active;
 public:
  OptionsMenu(TTF_Font *f,int maxw,SDL_Color txtc,SDL_Surface *button,SDL_Surface *button_pressed);
  void Draw(SDL_Surface *screen);
  void AddOption(string option);
  void SetPosition(int x,int y);
  string getOptionPressed(int x,int y);
  void MakeHighlighted(int x,int y);
  bool IsActive();
  void SetActive(bool Active);
};

#endif
