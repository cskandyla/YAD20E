#include "WarriorStates.h"
#include "CharacterHandler.h"
#include "BasicCharacter.h"
#include "State.h"

WarriorReaction::WarriorReaction(CharacterHandler *s_handler):CharacterState(s_handler)
{
}

//Counterattack
void WarriorReaction::Execute()
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
      the_char->SetReactionDone(true);
    }
}
