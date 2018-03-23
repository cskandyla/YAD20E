#include "IncrementingSpell.h"
#include <SDL2/SDL.h>

#ifndef __CONE_SPELL__
#define __CONE_SPELL__

class ConeSpell:public IncrementingSpell
{

public:
  //load 3 tiles for each direction ->
  //       top
  //  top  mid
  //  mid  mid   1+range*2+2=3,5,7,etc
  //  bot  mid
  //       bot
  ConeSpell(SpellInfo *spell_info,BaseCharacter *caster,void (*Effect)(SpellStats *sp_stats),AnimatedEntity *spell_entity);
  virtual ~ConeSpell();
  virtual void Draw(SDL_Texture *screen);
  virtual void OnCast();
};

#endif
