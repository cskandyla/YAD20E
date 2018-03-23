#include "Spell.h"
#include "animation.h"

#ifndef __INCREMENINTINGSPELL__
#define __INCREMENINTINGSPELL__

class IncrementingSpell: public Spell
{
protected:
  AnimatedEntity *spell_entity;
  int increment;
public:
  IncrementingSpell(SpellInfo *spell_info,BaseCharacter *caster,void (*Effect)(SpellStats *sp_stats),AnimatedEntity *spell_entity);
  virtual ~IncrementingSpell();
  virtual void Update(float time);
  virtual void Draw(SDL_Texture *screen);
  virtual void OnCast();
  virtual void OnDone();
  void Reset();
};

#endif
