#include "Warrior.h"
#include "Die.h"
#include "CharacterHandler.h"
#include "WarriorStates.h"


Warrior::  Warrior(AnimatedEntity *base,Info *myinfo, Attributes *BaseAttributes,GeneralStats *generalStats,CombatStats *combatStats)
  :BaseCharacter(base,myinfo,BaseAttributes,generalStats,combatStats)
{
  mastery=W_NO_M;
  stateHandler->AddState(STATE_REACTION,new WarriorReaction(stateHandler));
  
}

Warrior::Warrior(AnimatedEntity *base,Info *myinfo, Attributes *BaseAttributes,GeneralStats *generalStats,CombatStats *combatStats,WARRIOR_MASTERY mastery)
:BaseCharacter(base,myinfo,BaseAttributes,generalStats,combatStats)
{
  this->mastery=mastery;
  
  
}

bool Warrior::DamageRoll(BaseCharacter *targetent)
{
  int dmgdone=Die::Roll(this->getCombatStats()->getDamage(),1);
  int strbonus=(getCurrentAttributes()->getStr()-10)/2;
  if(strbonus>0)
    dmgdone+=strbonus;
  if(getGeneralStats()->getLevel()>=5 /* && holds a two handed weapon */)
    {
      dmgdone+=Die::Roll(8,2);
    }
  targetent->getGeneralStats()->SetHp(targetent->getGeneralStats()->getHp()-dmgdone);
  cout<<"Warrior Doing "<<dmgdone<<" to "<<targetent->getInfo()->getName()<<" Hp remaining:"<<targetent->getGeneralStats()->getHp()<<endl; 

  return true;
}

bool Warrior::AttackRoll(BaseCharacter *targetent)
{
  int d20roll=Die::Roll(20,1)+Die::Roll(4,1);
  cout<<"Testing Tohit:"<<d20roll+this->getCombatStats()->getTohitBonus()<<" vs "<<targetent->getCombatStats()->getArmorClass()<<endl;
  if(d20roll+this->getCombatStats()->getTohitBonus()>=targetent->getCombatStats()->getArmorClass())
    return true;
  return false;
}

bool Warrior::Cleave(BaseCharacter *ent)
{
  if(getGeneralStats()->getLevel()>=4)
    {
      cout<<"target:"<<ent->getInfo()->getName()<<endl;
      if(getID() != ent->getID() && (mainHand!= NULL))
	{

	  SetTarget(ent);
	  int dist=abs(ent->getPosition().x-this->getPosition().x)/TILE_SIZE+abs(ent->getPosition().y-this->getPosition().y)/TILE_SIZE;
	  if(mainHand->getInfo()->getRange() >=  dist)
	    {
	      //ABILITY STATE
	      stateHandler->SetState(STATE_CLEAVE);
	      SetUpAttackAnimation(ent);
	  
	      if(mainHand->getInfo()->getRange()>1)
		{
		  if(projectile)
		    delete projectile;
		  projectile=new Projectile(ammo->getEntity(),GetTarget()->GetBaseEntity()->getRect(),10);
		  projectile->Place(GetBaseEntity()->getPosition(),dir);
		  projectile->SetUp();
		  projectile->Reset();

		}
	      return true;
	    }
	}
    
    }
  return false;
}
bool Warrior::Reaction(BaseCharacter *ent)
{
  if(getGeneralStats()->getLevel()>=4)
    {
      if(getID() != ent->getID() && (mainHand!= NULL))
	{

	  SetTarget(ent);
	  int dist=abs(ent->getPosition().x-this->getPosition().x)/TILE_SIZE+abs(ent->getPosition().y-this->getPosition().y)/TILE_SIZE;
	  if(mainHand->getInfo()->getRange() >=  dist)
	    {
	      //ABILITY STATE
	      stateHandler->SetState(STATE_REACTION);
	      SetUpAttackAnimation(ent);
	      SetReactionDone(false);
	  
	      if(mainHand->getInfo()->getRange()>1)
		{
		  if(projectile)
		    delete projectile;
		  projectile=new Projectile(ammo->getEntity(),GetTarget()->GetBaseEntity()->getRect(),10);
		  projectile->Place(GetBaseEntity()->getPosition(),dir);
		  projectile->SetUp();
		  projectile->Reset();
		}
	      return true;
	    }
	}
    }
  return false;
}

void Warrior::CalculateCombatStats()
{
  BaseCharacter::CalculateCombatStats();
  if(mastery=W_SHIELD_M /* &&  Wears a shield*/) 
  getCombatStats()->SetArmorClass(getCombatStats()->getArmorClass()+4);
}
