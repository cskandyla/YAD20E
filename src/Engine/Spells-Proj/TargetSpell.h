#include <SDL2/SDL.h>
#include "Spell.h"
#include "Projectile.h"
#ifndef __TARGETSPELL_H
#define __TARGETSPELL_H

class TargetSpell:public Spell
{

 private:
  Projectile *projectile;
  AnimatedEntity *animated_entity;
 public:
  TargetSpell(SpellInfo *spell_info,BaseCharacter *caster,void (*Effect)(SpellStats *sp_stats),AnimatedEntity *animated_entity);
  TargetSpell(const TargetSpell &aspell);
  virtual ~TargetSpell();
 virtual void Update(float time);
 virtual void Draw(SDL_Texture *screen);
 virtual void OnCast();
 virtual void OnDone();
 void Place();
 void Reset();
  

};

#endif
