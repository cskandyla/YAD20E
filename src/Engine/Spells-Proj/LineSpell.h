#include "IncrementingSpell.h"
#ifndef __LINESPELL__
#define __LINESPELL__

class LineSpell: public IncrementingSpell
{

public:
  LineSpell(SpellInfo *spell_info,BaseCharacter *caster,void (*Effect)(SpellStats *sp_stats),AnimatedEntity *spell_entity);
  virtual ~LineSpell();
  virtual void Draw(SDL_Texture *screen);
  virtual void OnCast();
};

#endif
