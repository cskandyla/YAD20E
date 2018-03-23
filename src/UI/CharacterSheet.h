#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include "Info.h"
#include "Stats.h"
#include <string>
using std::string;


#ifndef __CHARACTER_SHEET_H
#define __CHARACTER_SHEET_H


class BaseCharacter;
class CharacterSheet
{
 private:
  Attributes *attribs;
  GeneralStats *stats;
  CombatStats *combatstats;
  Info *info;
  TTF_Font *desc_font;
  SDL_Texture *sheet_surf;
  SDL_Texture *portrait;
  bool visible;
  void BuildInfo();
  void CreateTextPair(string label_txt,string info_txt,int x,int y);

 public:
  CharacterSheet(TTF_Font *desc_font,BaseCharacter *the_char,int w,int h);
  CharacterSheet(TTF_Font *desc_font,BaseCharacter *the_char,string);
  virtual ~CharacterSheet();
  void Draw(SDL_Renderer *screen);
  bool Shown();
  void Show(bool visible);
  
};




#endif
