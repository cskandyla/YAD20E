#include <vector>
#include <string>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include "ButtonMenu.h"
#include "Caster.h"
#include "Camera.h"
#include "TurnEngine.h"
using std::vector;
using std::string;

#ifndef __SPELL_INTERFACE_H
#define __SPELL_INTERFACE_H

class SpellInterface
{
 private:
  ButtonMenu *level_buttons;
  vector<ButtonMenu*> spell_buttons;
  Caster *caster;
  Camera *camera;
  TurnEngine *t_e;
  unsigned int num_spells;
  public:
  SpellInterface(TurnEngine *t_e,Caster *caster,Camera *camera);
  SpellInterface(TurnEngine *t_e,Caster *caster,Camera *camera,SDL_Rect starting_pos);
  virtual ~SpellInterface();
  void HandleEvents(SDL_Event *event);
  void Draw(SDL_Texture *screen);
  void UpdatePreparedSpells();
};

#endif
