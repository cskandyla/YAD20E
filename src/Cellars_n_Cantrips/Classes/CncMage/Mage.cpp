#include "Mage.h"
#include "CharacterHandler.h"
Mage::Mage(AnimatedEntity *base,Info *myinfo, Attributes *BaseAttributes,GeneralStats *generalStats,CombatStats *combatStats):
  Caster(base,myinfo,BaseAttributes,generalStats,combatStats)
{
  
}

Mage::Mage(AnimatedEntity *base,Info *myinfo, Attributes *BaseAttributes,GeneralStats *generalStats,CombatStats *combatStats,enum SPELL_SCHOOL school ,enum MAGE_MASTERY mastery):
  Caster(base,myinfo,BaseAttributes,generalStats,combatStats)
{
  if(getGeneralStats()->getLevel()>=2)
    {
      SchoolSpecialization(school);
    }
  if(getGeneralStats()->getLevel()>=5)
    {
      if(mastery==M_ARCANE_M)
	ArcaneMastery();
      else if(mastery==M_SPELL_M)
	SpellMastery();
    }
}


Mage::~Mage()
{
    
}

bool Mage::Prepare(string spellName)
{
    if(Spells.find(spellName)!=Spells.end())
    {
       the_spell=Spells[spellName];
       if(the_spell->GetSpellStats()->GetLevel()>0 || Prepared.find(spellName)==Prepared.end())
	 {
	   Prepared.insert(spellName);
	   return true;
	 }
    }
    return false;
  

}


bool Mage::LearnSpell(Spell *the_spell)
{
  cout<<"Learning:"<<the_spell->GetSpellInfo()->getName()<<endl;
  if(the_spell->GetSpellInfo()->getClass().compare("Mage")==0 &&  ceil(getGeneralStats()->getLevel()/2.0)>=the_spell->GetSpellStats()->GetLevel())
    {
      
      Caster::LearnSpell(the_spell);
      cout<<"Added:"<<the_spell->GetSpellInfo()->getName()<<"to my spellbook"<<endl;
      return true;
      
    }
  cout<<"Failed to learn:"<<the_spell->GetSpellInfo()->getName()<<endl;
  delete the_spell;
  return false;
}

void Mage::SchoolSpecialization(enum SPELL_SCHOOL school)
{
  cout<<"Applying School Specialization"<<endl;
  GetCasterStats()->SetMastery(school,GetCasterStats()->GetMastery(school)+1);
}

void Mage::SpellMastery()
{
  cout<<"Applying Spell Mastery"<<endl;
  for(int i=0;i<8;i++)
    {
      GetCasterStats()->SetMastery(i,GetCasterStats()->GetMastery(i)+1);
    }
}
void Mage::ArcaneMastery()
{
  cout<<"Applying Arcane Mastery"<<endl;
  for(int i=0;i<6;i++)
    for(int j=0;j<10;j++)
      {
	int num_slots=GetCasterStats()->GetSpellSlots(i,j);
	if(num_slots)
	  GetCasterStats()->SetSpellSlots(i,j,num_slots+1);
      }
}

bool Mage::Reaction(BaseCharacter *ent)
{
	return false;
  /*
  cout<<"Mage Reaction"<<endl;
   the_spell=NULL;
   string spellName="Mage Armor";
   
  unordered_map<string,Spell*>::iterator it=Spells.begin();
  if(Spells.find(spellName)==Spells.end())
    {
      cout<<"Spell Not Prepared or Known"<<endl;
      return false;
    }
  else  if(Prepared.find(spellName)!=Prepared.end()  && Spells.find(spellName)!=Spells.end())
    {
      the_spell=Spells[spellName];
    }
  if(the_spell!=NULL)
    {
      //Find a better place to put this
      pair<int,int> spelltarget(getPosition().x,getPosition().y);
      the_spell->GetSpellStats()->SetTarget(spelltarget);
      
      if(the_spell->IsValidTarget())
	{
	  SetCastAnimation(spelltarget);
	  stateHandler->SetState(REACTION_S);
	  SetReactionDone(false);
	   if(the_spell->GetSpellStats()->GetLevel()>0)
	     Prepared.erase(Prepared.find(spellName));
	  return true;
	}
    }
  return false;	  
  */
}
