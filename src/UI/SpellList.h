#include <vector>
#include <string>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include "ButtonMenu.h"
#include "Caster.h"
using std::vector;
using std::string;

#ifndef __SPELL_LIST_H__
#define __SPELL_LIST_H__



class SpellList
{
 private:
  Caster *caster;
  SDL_Texture *Preparedlbl,*Knownlbl;
  vector<SDL_Texture*> Labels;
  vector<ButtonMenu*> Prepared;
  vector<ButtonMenu*> All;
  bool shown;
 public:
  SpellList(TTF_Font *font,Caster *caster);
  virtual ~SpellList();
  void HandleEvents(SDL_Event *event);
  void Draw(SDL_Texture *screen);

  //Add-Remove Single Spell
  bool Prepare(Button *button,int level);
  bool Forget(Button *button,int level);

  //Clear
  void ClearAll();
  void ClearMenu(int level);

  void Show(bool shown);
  bool Shown();
  vector<ButtonMenu*>& GetPrepared();

};


#endif
