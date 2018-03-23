#include "BasicCharacter.h"

#ifndef __WARRIOR_H
#define __WARRIOR_H

//Lvl1: +D4 on attack rolls/+2AC
//Lvl2: Knockdown
//Lvl3: Counter attack reaction
//Lvl4: Cleave
//Lvl5: Expert Strike: Double Weapon Die+

enum WARRIOR_MASTERY{W_TWOHANDED_M,W_SHIELD_M,W_NO_M};
class Warrior:public BaseCharacter
{
private:
  enum WARRIOR_MASTERY mastery;
public:
  Warrior(AnimatedEntity *base,Info *myinfo, Attributes *BaseAttributes,GeneralStats *generalStats,CombatStats *combatStats);
  Warrior(AnimatedEntity *base,Info *myinfo, Attributes *BaseAttributes,GeneralStats *generalStats,CombatStats *combatStats,WARRIOR_MASTERY mastery);
	  
  virtual bool DamageRoll(BaseCharacter *targetent);
  virtual bool AttackRoll(BaseCharacter *targetent);
  virtual void CalculateCombatStats();
  bool Cleave(BaseCharacter *ent);
  virtual bool Reaction(BaseCharacter *ent);//Counter
};

#endif
