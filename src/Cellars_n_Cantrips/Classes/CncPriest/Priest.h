#include "Caster.h"

#ifndef __PRIEST_H
#define __PRIEST_H


//Lvl1:  --
//Lvl2:  Divine Word: Word of Light (Lay on Hands), Word of Darkness(Inverse Lay on Hands), Word of Might(+Str,+Con)
//Lvl3:  --
//Lvl4:  Divine Radiance: Aura Heals/Damages/Buffs for 1 round
//Lvl5:  --
//Lvl6:  Divine Mastery: +3 on chosen school

class Priest:
public Caster
{
 private:
  
 public:
  Priest(AnimatedEntity *base,Info *myinfo, Attributes *BaseAttributes,GeneralStats *generalStats,CombatStats *combatStats);
  virtual ~Priest();
  virtual bool LearnSpell(Spell *the_spell);


};

#endif
