#include "BasicCharacter.h"
#include "CharacterHandler.h"
#include "CharacterState.h"
#include "Die.h"
#include <iostream>
#include <sstream>
using std::cout;
using std::endl;
using std::stringstream;




BaseCharacter::BaseCharacter(AnimatedEntity *base,Info *myinfo, Attributes *BaseAttributes,GeneralStats *generalStats,CombatStats *combatStats):BaseEntity(base),info(myinfo),
																		BaseAttributes(BaseAttributes),generalStats(generalStats),
																		combatStats(combatStats)
{
  this->portrait=NULL;
  this->hasMoved=false;
  this->chest=NULL;
  this->head=NULL;
  this->mainHand=NULL;
  this->secondaryHand=NULL;
  this->legs=NULL;
  this->neck=NULL;
  this->hand1=NULL;
  this->hand2=NULL;
  this->ammo=NULL;
  //Copy
  this->originalStats=new GeneralStats(generalStats->getHp(),generalStats->getSpeed(),generalStats->getXp());
  this->currentAttributes=new Attributes(BaseAttributes->getStr(),BaseAttributes->getDex(),BaseAttributes->getCon(),BaseAttributes->getInt(),BaseAttributes->getSpi());
  this->Log=NULL;
  projectile=NULL;
  dir=RIGHT;
  this->stateHandler=new CharacterHandler(this);
  stateHandler->AddState(STATE_STAND,new CharacterStand(stateHandler));
  stateHandler->AddState(STATE_MOVE,new CharacterMove(stateHandler));
  stateHandler->AddState(STATE_ATTACK,new CharacterAttack(stateHandler));
  stateHandler->AddState(STATE_DYING,new CharacterDying(stateHandler));
  stateHandler->AddState(STATE_DEAD,new CharacterDead(stateHandler));
  stateHandler->SetState(STATE_STAND);
}

BaseCharacter::BaseCharacter(AnimatedEntity *base,Info *myinfo, Attributes *BaseAttributes,GeneralStats *generalStats,CombatStats *combatStats,CharacterHandler *s_handler):BaseEntity(base),info(myinfo),
																		BaseAttributes(BaseAttributes),generalStats(generalStats),
																			 combatStats(combatStats),stateHandler(s_handler)
{
  this->portrait=NULL;
  this->hasMoved=false;
  this->chest=NULL;
  this->head=NULL;
  this->mainHand=NULL;
  this->secondaryHand=NULL;
  this->legs=NULL;
  this->neck=NULL;
  this->hand1=NULL;
  this->hand2=NULL;
  this->ammo=NULL;
  //Copy
  this->originalStats=new GeneralStats(generalStats->getHp(),generalStats->getSpeed(),generalStats->getXp());
  this->currentAttributes=new Attributes(BaseAttributes->getStr(),BaseAttributes->getDex(),BaseAttributes->getCon(),BaseAttributes->getInt(),BaseAttributes->getSpi());
  this->Log=NULL;
  projectile=NULL;
  dir=RIGHT;
  this->stateHandler=new CharacterHandler(this);
  stateHandler->AddState(STATE_STAND,new CharacterStand(stateHandler));
  stateHandler->AddState(STATE_MOVE,new CharacterMove(stateHandler));
  stateHandler->AddState(STATE_ATTACK,new CharacterAttack(stateHandler));
  stateHandler->AddState(STATE_DYING,new CharacterDying(stateHandler));
  stateHandler->AddState(STATE_DEAD,new CharacterDead(stateHandler));
  stateHandler->SetState(STATE_STAND);
}

BaseCharacter::~BaseCharacter()
{
  cout<<"Deleting:"<<info->getName()<<endl;
  if(portrait)
    SDL_DestroyTexture(portrait);
  cout<<"Deleting stats"<<endl;
  delete BaseAttributes;
  delete currentAttributes;
  delete originalStats;
  delete BaseEntity;
  delete info;
  delete generalStats;
  delete combatStats;

  //Delete all items;
  cout<<"Deleting items"<<endl;
  cout<<"Chest"<<endl;
  if(chest)
    delete chest;
  cout<<"Head"<<endl;
  if(head)
    delete head;
  if(mainHand)
    delete mainHand;
  if(secondaryHand)
    delete secondaryHand;
  if(legs)
    delete legs;
  if(neck)
    delete neck;
  cout<<"Hands and stuff"<<endl;
  if(hand1)
    delete hand1;
  if(hand2)
    delete hand2;
  if(ammo)
    delete ammo;
  if(Log)
    delete Log;
  if(projectile)
    delete projectile;

  //Delete inventory
  cout<<"Deleting Inventory"<<endl;
  for(int i=0;i<Inventory.size();i++)
    {
      delete Inventory[i];
    }
  cout<<"Deleting StateHandler"<<endl;
  if(stateHandler)
    delete stateHandler;
  
}


int BaseCharacter::getID()
{
  return ID;
}

void BaseCharacter::setID(int id)
{
  ID=id;
}

void BaseCharacter::SetPortrait(SDL_Texture *portrait)
{
  this->portrait=portrait;
}
SDL_Texture* BaseCharacter::GetPortrait()
{
  return portrait;
}

AnimatedEntity* BaseCharacter::GetBaseEntity()
{
  return this->BaseEntity;
}

Armor* BaseCharacter::GetChest()
{
  return this->chest;
}
Weapon* BaseCharacter::GetMainHand()
{
  return this->mainHand;
}

void BaseCharacter::Draw(SDL_Texture *screen)
{
  this->BaseEntity->Draw(screen);
  if(this->head!=NULL)
  this->head->Draw(screen);
  if(this->chest!=NULL)
  this->chest->Draw(screen);
  if(this->secondaryHand!=NULL)
    this->secondaryHand->Draw(screen);
  if(this->mainHand!=NULL)
    this->mainHand->Draw(screen);
  if(projectile && projectile->IsActive())
    projectile->Draw(screen);
}


void BaseCharacter::SetAnimation(ANIMS anim)
{
  this->BaseEntity->setAnimation(anim);
  if(chest!=NULL)
    this->chest->setAnimation(anim);
    if(head!=NULL)
    this->head->setAnimation(anim);
  if(mainHand!=NULL)
    this->mainHand->setAnimation(anim);
  if(this->secondaryHand!=NULL)
    this->secondaryHand->setAnimation(anim);
}

void BaseCharacter::Update(float time)
{
  this->BaseEntity->Update(time);
  if(this->head!=NULL)
    this->head->Update(time);
  if(this->chest!=NULL)
    this->chest->Update(time);
  if(this->secondaryHand!=NULL)
    this->secondaryHand->Update(time);
  if(this->mainHand!=NULL)
    this->mainHand->Update(time);
  
  //  HandleEffects();
  HandleState(time);
  HandleProjectile(time);
}


void BaseCharacter::SetPosition(int xpos,int ypos)
{
  this->BaseEntity->setPosition(xpos,ypos);
  if(head!=NULL)
    head->setPosition(xpos,ypos);
  if(chest!=NULL)
    chest->setPosition(xpos,ypos);
  if(mainHand!=NULL)
    mainHand->setPosition(xpos,ypos);
  if(this->secondaryHand!=NULL)
    this->secondaryHand->setPosition(xpos,ypos);
}

void BaseCharacter::SetVelocity(int xvel,int yvel)
{
  this->BaseEntity->SetVelocity(xvel,yvel);
  if(head!=NULL)
    head->SetVelocity(xvel,yvel);
  if(mainHand!=NULL)
    mainHand->SetVelocity(xvel,yvel);
  if(chest!=NULL)
    chest->SetVelocity(xvel,yvel);
  if(this->secondaryHand!=NULL)
    this->secondaryHand->SetVelocity(xvel,yvel);
}


void BaseCharacter::HandleState(float t)
{

  //IsDying?
  if(generalStats->getHp()<=0 && !(stateHandler->GetCurrentStateNum()==STATE_DYING || stateHandler->GetCurrentStateNum()==STATE_DEAD))
    {
      SetReactionDone(true);
      stateHandler->SetState(STATE_DYING);
      SetAnimation(DYING_A);
    }
  stateHandler->Update();
}
void BaseCharacter::HandleProjectile(float t)
{
  //HandleProjectile
  if(projectile && projectile->Hit())
    {
      if(AttackRoll(target))
	DamageRoll(target);
      projectile->Reset();
    }

  if(projectile && projectile->IsActive())
    projectile->Update(t);


}
void BaseCharacter::HandleEffects()
{
  //Handle Effects
  for(int i=0;i<status_effects.size();i++)
    {
      if(status_effects[i]->getDuration()==0 && !status_effects[i]->IsPermanent())
	{
	  Effect *eff=status_effects[i];
	  status_effects.erase(status_effects.begin()+i);
	  delete eff;
	}
      else
	{
	  status_effects[i]->ApplyEffect();
	}
    }
}

void BaseCharacter::OnTurnStart()
{
  //
  //By default we're just handling effects
  
  HandleEffects();
  movementleft=generalStats->getSpeed();
}



void BaseCharacter::SwitchMainWeapon(Weapon *mhand)
{
  cout<<"Switching main weapon to:"<<mhand<<':'<<mhand->getInfo()->getName()<<endl;
  if(mhand == NULL)
    this->mainHand=NULL;
  else
    {
      if(mhand->getInfo()->getItemSlot()==MainWeapon)
        {
	  cout<<"Equiping: "<<mhand->getInfo()->getName()<<endl;
	  this->mainHand=mhand;
	  this->mainHand->SetPosition(this->BaseEntity->getPosition().x,this->BaseEntity->getPosition().y);
	  ToLog("Weapon Loaded: "+mainHand->getInfo()->getName());
        }
      else
	{
	  this->mainHand=NULL;
	}
    }
  //ToLog(winfo->InfoString());


}

void BaseCharacter::SwitchSecondaryWeapon(Weapon *shand)
{


  if(shand == NULL)
    this->secondaryHand=NULL;
  else
    {
      if(shand->getInfo()->getItemSlot()==SecondWeapon)
        {
	  cout<<"Equiping: "<<shand->getInfo()->getName()<<endl;
	  this->secondaryHand=shand;
	  ToLog("Weapon Loaded: "+secondaryHand->getInfo()->getName());
        }
    }
  //ToLog(winfo->InfoString());


}


void BaseCharacter::SwitchArmor(Armor *armor)
{
  if (armor == NULL)
    this->chest = NULL;
  else
    {
      if(armor->getInfo()->getItemSlot()==Chest)
        {
	  this->chest=armor;
        }
    }
}

void BaseCharacter::SwitchHead(VisibleItem *item)
{
  if (item == NULL)
    this->head = NULL;

  else
    {
      if(item->getInfo()->getItemSlot()==Head)
        {
	  this->head=item;
        }
    }
}

void BaseCharacter::SwitchLegs(VisibleItem *item)
{
  if (item == NULL)
    this->legs = NULL;

  else
    {
      if(item->getInfo()->getItemSlot()==Legs)
        {
	  this->legs=item;
        }
    }
}



void BaseCharacter::SwitchNeck(Item *item)
{
  if (item == NULL)
    this->neck = NULL;

  else
    {
      if(item->getInfo()->getItemSlot()==Neck)
        {
	  this->neck=item;
        }
    }
}

void BaseCharacter::SwitchHand1(Item *item)
{
  if (item == NULL)
    this->hand1 = NULL;

  else
    {
      if(item->getInfo()->getItemSlot()==Hand1)
        {
	  this->hand1=item;
        }
    }
}

void BaseCharacter::SwitchHand2(Item *item)
{
  if (item == NULL)
    this->hand2 = NULL;

  else
    {
      if(item->getInfo()->getItemSlot()==Hand2)
        {
	  this->hand2=item;
        }
    }
}



Item* BaseCharacter::getSlot(ITEMSLOT slot)
{

  switch(slot)
    {
    case Head:
      return head;
      break;
    case Chest:
      return chest;
      break;
    case Legs:
      return legs;
      break;
    case Neck:
      return neck ;
      break;
    case Hand1:
      return hand1 ;
      break;
    case Hand2:
      return hand2 ;
      break;
    case MainWeapon:
      return mainHand ;
      break;
    case SecondWeapon:
      return secondaryHand ;
      break;
    }

}

void BaseCharacter::Move(list<DIRECTION> path)
{
  this->path=path;
  stateHandler->SetState(STATE_MOVE);
}

int BaseCharacter::GetMovementLeft()
{
  return movementleft;
}
void BaseCharacter::SetMovementLeft(int movementleft)
{
  this->movementleft=movementleft;
}

list<DIRECTION>* BaseCharacter::GetPath()
{
  return &this->path;
}

void BaseCharacter::SetDirection(DIRECTION dir)
{
  this->dir=dir;
}
DIRECTION BaseCharacter::GetDirection()
{
  return this->dir;
}


void BaseCharacter::Ability()
{

}


Item* BaseCharacter::getInventorySlot(int slotnum)
{
  if(Inventory.size()>slotnum)
  return this->Inventory[slotnum];
  else
    return NULL;
}
Item* BaseCharacter::getInventoryItem(string name)
{
  for(int i=0;i<Inventory.size();i++)
    {
      cout<<"comparing:"<<name<<" to:"<<Inventory[i]->getInfo()->getName()<<endl;
      if(Inventory[i]->getInfo()->getName().compare(name)==0)
	return Inventory[i];
    }
  return NULL;
  
}

void BaseCharacter::Equip(Item *item)
{
  cout<<"Slot is:"<<item->getInfo()->getItemSlot()<<endl;
  switch(item->getInfo()->getItemSlot())
    {
    case Head:
      head=dynamic_cast<VisibleItem*>(item);
      break;
    case Chest:
      SwitchArmor(dynamic_cast<Armor*>(item));
      break;
    case Legs:
      legs=dynamic_cast<VisibleItem*>(item);
      break;
    case Neck:
      neck=item;
      break;
    case Hand1:
      hand1=item;
      break;
    case Hand2:
      hand2=item;
      break;
    case SecondWeapon:
      SwitchSecondaryWeapon(dynamic_cast<Weapon*>(item));
      break;
    case MainWeapon:
      cout<<"Trying to cast to Weapon*"<<endl;
      SwitchMainWeapon(dynamic_cast<Weapon*>(item));
      break;
    case Ammo:
      ammo=dynamic_cast<VisibleItem*>(item);;
      break;
    }
  CalculateCombatStats();
  cout<<"Item Equiped"<<endl;
}


void BaseCharacter::CalculateCombatStats()
{
  int BaseAttackBonus=0;
  int ToHitBonus=(currentAttributes->getStr()-10)/2;
  int Damage=(currentAttributes->getStr()-10)/2;
  int ArmorClass=(currentAttributes->getDex()-10)/2+10;
  int Sr=0;
  if(mainHand!=NULL)
    {
      if(mainHand->getInfo()->getRange()==1)
        {
	  ToHitBonus+=mainHand->getInfo()->getToHitBonus();
	  Damage=mainHand->getInfo()->getDamage();
        }
      else if(mainHand->getInfo()->getRange()>1)
        {
	  ToHitBonus=(currentAttributes->getDex()-10)/2+mainHand->getInfo()->getToHitBonus();
	  Damage=mainHand->getInfo()->getDamage();
        }
    }
  if(chest!=NULL)
    {
      ArmorClass+=chest->getInfo()->getBaseDef();
    }
  combatStats->SetToHitBonus(ToHitBonus);
  combatStats->SetDamage(Damage);
  combatStats->SetArmorClass(ArmorClass);
}
void BaseCharacter::SetUpAttackAnimation(BaseCharacter *ent)
{
  if(mainHand->getInfo()->getDamageType()==SLASHING || mainHand->getInfo()->getDamageType()==FORCE)
    {

      int x=this->getPosition().x-ent->getPosition().x;
      int y=this->getPosition().y-ent->getPosition().y;
      if(abs(x)>abs(y))
	{
	  if(x>0)
	    {
	      dir=LEFT;
	      SetAnimation(SLASH_L);
	    }
	  else
	    {
	      dir=RIGHT;
	      SetAnimation(SLASH_R);
	    }
	}
      else
	{
	  if(y>0)
	    {
	      dir=UP;
	      SetAnimation(SLASH_U);
	    }
	  else
	    {
	      dir=DOWN;
	      SetAnimation(SLASH_D);
	    }

	}

    }
  else if(mainHand->getInfo()->getDamageType()==PIERCING )
    {

      if(this->getPosition().x-ent->getPosition().x<0)
	{
	  dir=RIGHT;
	  if(mainHand->getInfo()->getRange()>1)
	    SetAnimation(SHOOT_R);
	  else
	    SetAnimation(THRUST_R);
	}
      else if(this->getPosition().x-ent->getPosition().x>0)
	{
	  dir=LEFT;
	  if(mainHand->getInfo()->getRange()>1)
	    SetAnimation(SHOOT_L);
	  else
	    SetAnimation(THRUST_L);
	}
      else if(this->getPosition().y-ent->getPosition().y<0)
	{
	  dir=DOWN;
	  if(mainHand->getInfo()->getRange()>1)
	    SetAnimation(SHOOT_D);
	  else
	    SetAnimation(THRUST_D);
	}
      else if(this->getPosition().y-ent->getPosition().y>0)
	{
	  dir=UP;
	  if(mainHand->getInfo()->getRange()>1)
	    SetAnimation(SHOOT_U);
	  else
	    SetAnimation(THRUST_U);
	}
    }
}

bool BaseCharacter::AttackRoll(BaseCharacter *targetent)
{

  int d20roll=Die::Roll(20,1);
  cout<<"Testing Tohit:"<<d20roll+this->getCombatStats()->getTohitBonus()<<" vs "<<targetent->getCombatStats()->getArmorClass()<<endl;
  if(d20roll+this->getCombatStats()->getTohitBonus()>=targetent->getCombatStats()->getArmorClass())
    return true;
  return false;
	    
}
bool BaseCharacter::DamageRoll(BaseCharacter *targetent)
{
  int dmgdone=Die::Roll(this->getCombatStats()->getDamage(),1);
  targetent->getGeneralStats()->SetHp(targetent->getGeneralStats()->getHp()-dmgdone);
  cout<<"Doing "<<dmgdone<<" to "<<targetent->getInfo()->getName()<<" Hp remaining:"<<target->getGeneralStats()->getHp()<<endl; 
}

void BaseCharacter::Walk(DIRECTION dir)
{
  	  switch  (dir)
            {
            case UP:
	      {
                SetDirection(UP);
                SetAnimation(WALK_U);
                BaseEntity->SetDestination(BaseEntity->getPosition().x,BaseEntity->getPosition().y-TILE_SIZE);
		if(head!=NULL)
		  {
		    head->SetDestination(mainHand->getPosition().x,mainHand->getPosition().y-TILE_SIZE);
		  }

                if(mainHand!=NULL)
		  {
                    mainHand->SetDestination(mainHand->getPosition().x,mainHand->getPosition().y-TILE_SIZE);

		  }
                if(chest!=NULL)
		  {
                    chest->SetDestination(chest->getPosition().x,chest->getPosition().y-TILE_SIZE);
		  }
		if(secondaryHand!=NULL)
		  {
		    secondaryHand->SetDestination(secondaryHand->getPosition().x,secondaryHand->getPosition().y-TILE_SIZE);
		  }
	      }
	      break;
            case DOWN:
	      {
                SetDirection(DOWN);
                SetAnimation(WALK_D);
                BaseEntity->SetDestination(BaseEntity->getPosition().x,BaseEntity->getPosition().y+TILE_SIZE);
                if(head!=NULL)
		  {
                    head->SetDestination(mainHand->getPosition().x,mainHand->getPosition().y+TILE_SIZE);
		  }
		if(mainHand!=NULL)
		  {
                    mainHand->SetDestination(mainHand->getPosition().x,mainHand->getPosition().y+TILE_SIZE);
		  }
                if(chest!=NULL)
		  {
                    chest->SetDestination(chest->getPosition().x,chest->getPosition().y+TILE_SIZE);
		  }
		if(secondaryHand!=NULL)
		  {
		    secondaryHand->SetDestination(secondaryHand->getPosition().x,secondaryHand->getPosition().y+TILE_SIZE);
		  }
	      }
	      break;
            case LEFT:
	      {
                SetDirection(LEFT);
                SetAnimation(WALK_L);
                BaseEntity->SetDestination(BaseEntity->getPosition().x-TILE_SIZE,BaseEntity->getPosition().y);
                if(head!=NULL)
		  {
                    head->SetDestination(mainHand->getPosition().x-TILE_SIZE,mainHand->getPosition().y);
		  }
		if(mainHand!=NULL)
		  {
                    mainHand->SetDestination(mainHand->getPosition().x-TILE_SIZE,mainHand->getPosition().y);
		  }
                if(chest!=NULL)
		  {
                    chest->SetDestination(chest->getPosition().x-TILE_SIZE,chest->getPosition().y);
		  }
		if(secondaryHand!=NULL)
		  {
		    secondaryHand->SetDestination(secondaryHand->getPosition().x-TILE_SIZE,secondaryHand->getPosition().y);
		  }
	      }
	      break;
            case RIGHT:
	      {
                SetDirection(RIGHT);
                SetAnimation(WALK_R);
                BaseEntity->SetDestination(BaseEntity->getPosition().x+TILE_SIZE,BaseEntity->getPosition().y);
                if(head!=NULL)
		  {
                    head->SetDestination(mainHand->getPosition().x+TILE_SIZE,mainHand->getPosition().y);
		  }
		if(mainHand!=NULL)
		  {
                    mainHand->SetDestination(mainHand->getPosition().x+TILE_SIZE,mainHand->getPosition().y);
		  }
                if(chest!=NULL)
		  {
                    chest->SetDestination(chest->getPosition().x+TILE_SIZE,chest->getPosition().y);
		  }
		if(secondaryHand!=NULL)
		  {
		    secondaryHand->SetDestination(secondaryHand->getPosition().x+TILE_SIZE,secondaryHand->getPosition().y);
		  }
	      }
	      break;


            }
  
}

bool BaseCharacter::Attack(BaseCharacter *ent)
{
  cout<<"target:"<<ent->getInfo()->getName()<<endl;
  if(ID != ent->getID() && (mainHand!= NULL))
    {

      this->target=ent;
      int dist=abs(ent->getPosition().x-this->getPosition().x)/TILE_SIZE+abs(ent->getPosition().y-this->getPosition().y)/TILE_SIZE;
      if(mainHand->getInfo()->getRange() >=  dist)
        {
	  stateHandler->SetState(STATE_ATTACK);
	  SetUpAttackAnimation(ent);
	  
	  if(mainHand->getInfo()->getRange()>1)
            {
	      if(projectile)
		delete projectile;
	      projectile=new Projectile(ammo->getEntity(),this->target->GetBaseEntity()->getRect(),10);
	      projectile->Place(BaseEntity->getPosition(),dir);
	      projectile->SetUp();
	      projectile->Reset();

            }
	  return true;
        }
    }
  return false;
}

bool BaseCharacter::Reaction(BaseCharacter *ent)
{
  return false;
}

void BaseCharacter::ToLog(string s)
{
  if(Log!=NULL)
    {
      if(s.find('\n')==string::npos)
        {
	  Log->AddText(s,255,255,255);
        }
      else
        {
	  int pos=s.find('\n');
	  while(pos!=string::npos)
            {

	      Log->AddText(s.substr(0,pos),255,255,255);
	      s=s.substr(pos+1,s.length());
	      pos=s.find('\n');
            }
	  Log->AddText(s,255,255,255);
        }
    }


}

void BaseCharacter::setState(int s)
{
  this->stateHandler->SetState(s);
}


int BaseCharacter::getState()
{
  return this->stateHandler->GetCurrentStateNum();
}

void BaseCharacter::SetProjectile(Projectile *proj)
{
  this->projectile=proj;
  //  proj->SetPosition(BaseEntity->getPosition().x,BaseEntity->getPosition().y-proj->getPosition().h);
}


Projectile* BaseCharacter::getProjectile()
{

  return this->projectile;

}


void BaseCharacter::SetTarget(BaseCharacter *target)
{
  this->target=target;
}
BaseCharacter* BaseCharacter::GetTarget()
{

  return this->target;
}

bool BaseCharacter::Active()
{
  if(stateHandler->GetCurrentStateNum()==STATE_STAND && (!projectile || !projectile->IsActive()))
    return false;
  return true;

}

void BaseCharacter::SetMoved(bool moved)
{
  this->hasMoved=moved;
}
void BaseCharacter::SetActionDone(bool actiondone)
{
  this->standardActionDone=actiondone;
}
bool BaseCharacter::Moved()
{
  return this->hasMoved;
}
bool BaseCharacter::ActionDone()
{
  return this->standardActionDone;
}

void BaseCharacter::SetReactionDone(bool reactiondone)
{
  this->reactiondone=reactiondone;
}
bool BaseCharacter::ReactionDone()
{
  return this->reactiondone;
}

void BaseCharacter::SetStateHandler(CharacterHandler *s_handler)
{
  if(this->stateHandler)
    delete this->stateHandler;
  this->stateHandler=s_handler;
}
CharacterHandler* BaseCharacter::GetStateHandler()
{
  return this->stateHandler;
}
