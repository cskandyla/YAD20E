#include "Priest.h"


Priest::Priest(AnimatedEntity *base,Info *myinfo, Attributes *BaseAttributes,GeneralStats *generalStats,CombatStats *combatStats)
  :Caster(base,myinfo,BaseAttributes,generalStats,combatStats)
{
  
}

Priest::~Priest()
{

}


bool Priest::LearnSpell(Spell *the_spell)
{
  cout<<"Learning:"<<the_spell->GetSpellInfo()->getName()<<endl;
  if(the_spell->GetSpellInfo()->getClass().compare("Priest")==0)
    {
      Spells[the_spell->GetSpellInfo()->getName()]=the_spell;
      the_spell->SetCaster(this);
      cout<<"Successfully learned:"<<the_spell->GetSpellInfo()->getName()<<endl;
      return true;
    }
  cout<<"Failed to learn:"<<the_spell->GetSpellInfo()->getName()<<endl;
  return false;
}
