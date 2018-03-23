#include "EOTSpell.h"

#ifndef __CLOUDSPELL__
#define __CLOUDSPELL__

class CloudSpell : public EOTSpell
{
public:
  CloudSpell(SpellInfo *spell_info,BaseCharacter *caster,void (*Effect)(SpellStats *sp_stats),AnimatedEntity *spell_entity,int duration);
  CloudSpell(const CloudSpell &aspell);
  virtual void Update(float time);
  virtual void Draw(SDL_Texture *screen);
  virtual void OnCast();
  virtual void OnDone();

};

#endif
