#include "CharacterState.h"
#include "BasicCharacter.h"
#include "MapIndex.h"
#include "CharacterHandler.h"
#include "Caster.h"

CharacterState::CharacterState(CharacterHandler *s_handler):s_handler(s_handler)
{
  the_char=s_handler->GetTheCharacter();
}

CharacterStand::CharacterStand(CharacterHandler *s_handler):CharacterState(s_handler)
{
}

void CharacterStand::Execute()
{
  DIRECTION dir = the_char->GetDirection();
  if(dir==RIGHT)
    the_char->SetAnimation(STAND_R);
  else if(dir==LEFT)
    the_char->SetAnimation(STAND_L);
  else if(dir==UP)
    the_char->SetAnimation(STAND_U);
  else if(dir==DOWN)
    the_char->SetAnimation(STAND_D);
}


CharacterMove::CharacterMove(CharacterHandler *s_handler):CharacterState(s_handler)
{
  cout<<"MoveState"<<endl;
}
void CharacterMove::Execute()
{
  // cout<<"Executing Move"<<endl;
  list<DIRECTION> *path=the_char->GetPath();
  AnimatedEntity* BaseEntity=the_char->GetBaseEntity();
      
       if(BaseEntity->reachedDestination())
	{
	  if(path->empty())
	    {
	      
	      MapIndex::Instance()->ComputeVision(the_char->getPosition());
	      MapIndex::Instance()->CharIndexUpdate(the_char,0,0);
	      s_handler->SetState(STATE_STAND);	      
	    }
	  else if(!path->empty())
	    {
	      MapIndex::Instance()->ComputeVision(the_char->getPosition());
	      the_char->Walk(path->front());
	      path->pop_front();
	    }
	  
	}
}

CharacterAttack::CharacterAttack(CharacterHandler *s_handler):CharacterState(s_handler)
{
}
void CharacterAttack::Execute()
{
   if(the_char->GetBaseEntity()->getCur_Anim()->Done())
    {
      Projectile *projectile=the_char->getProjectile();
      BaseCharacter *target=the_char->GetTarget();
      if(projectile!=NULL)
	{
	  projectile->MakeActive(true);
	}
      else
	{
	  if(the_char->AttackRoll(target))
	     the_char->DamageRoll(target);
	  
	}
      s_handler->SetState(STATE_STAND);
      
      if(target->Reaction(the_char))
	{
	  cout<<"Reacting"<<endl;
	  s_handler->SetState(STATE_REACTION);
	}
    }
}



CharacterDying::CharacterDying(CharacterHandler *s_handler):CharacterState(s_handler)
{
}
void CharacterDying::Execute()
{
   if(the_char->GetBaseEntity()->getCur_Anim()->Done())
    {
      s_handler->SetState(STATE_DEAD);
    }
}


CharacterDead::CharacterDead(CharacterHandler *s_handler):CharacterState(s_handler)
{
}
void CharacterDead::Execute()
{
  the_char->SetAnimation(DEAD_A);
}



CharacterCast::CharacterCast(CharacterHandler *s_handler):CharacterState(s_handler)
{
}
void CharacterCast::Execute()
{
   if(the_char->GetBaseEntity()->getCur_Anim()->Done())
    {	  
      s_handler->SetState(STATE_STAND);
      Caster *caster=dynamic_cast<Caster*>(the_char);
      if(caster)
	caster->GetSpell()->CastSpell();
    }
}

