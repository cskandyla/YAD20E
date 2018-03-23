#include <SDL2/SDL.h>
#include "Spell.h"
#include "Projectile.h"
#include "Blast.h"
#ifndef __SPELLBLAST_H
#define __SPELLBLAST_H

class SpellBlast:public Spell
{

 private:
  Projectile *projectile;
  AnimatedEntity *projectile_entity;
  Blast *blast;
 public:
  SpellBlast(SpellInfo *spell_info,BaseCharacter *caster,void (*Effect)(SpellStats *sp_stats),AnimatedEntity *projectile_entity,AnimatedEntity *blast_entity);
  SpellBlast(const SpellBlast &aspellblast);
 virtual ~SpellBlast();
 virtual void Update(float time);
 virtual void Draw(SDL_Texture *screen);
 virtual void OnCast();
 virtual void OnDone();
 void Place();
 void Reset();

};

#endif
