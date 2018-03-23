
#include <unordered_map>
#include <set>
#include <string>
using std::unordered_map;
using std::multiset;
using std::set;
using std::string;
#include "Caster.h"
#include "Spell.h"
//KISS
//Lvl 2: ??????? / Increase Evocation spell Range
//Lvl 4: +1 AOE  / Does Not Hit Allies
//Lvl 6: +1 Rank /+3 Ranks in evocation


#ifndef __MAGE__
#define __MAGE__

enum MAGE_MASTERY{M_ARCANE_M,M_SPELL_M,M_NO_M};
//enum MAGE_SCHOOLS{EVOCATION,ABJURATION,ALTERATION};

class Mage:public Caster
{
 private:
  BaseCharacter *counter_target;//has to be a caster so why bother?
 public:
  Mage(AnimatedEntity *base,Info *myinfo, Attributes *BaseAttributes,GeneralStats *generalStats,CombatStats *combatStats);
  Mage(AnimatedEntity *base,Info *myinfo, Attributes *BaseAttributes,GeneralStats *generalStats,CombatStats *combatStats,enum SPELL_SCHOOL school ,enum MAGE_MASTERY mastery);
  virtual ~Mage();//Destroy the spells
  //A Mage does not expend level-0 slots also add bonuses;
  virtual bool Prepare(string spellName);
  virtual bool LearnSpell(Spell *the_spell);
  virtual bool Reaction(BaseCharacter *ent);

  //Feats
  void Counterspell(BaseCharacter *target);
  void SchoolSpecialization(enum SPELL_SCHOOL school);
  void SpellMastery();
  void ArcaneMastery();
  
};

#endif
