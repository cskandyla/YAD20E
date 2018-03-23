
#include "Zombie.h"

#include "Astar.h"
#include "State_Wait.h"
#include "State_Chase.h"
#include "State_Attack.h"


Zombie_AI::Zombie_AI(BaseCharacter *the_char): AIEntity(the_char)
{
  this->cur_state=NULL;
  this->target = NULL;
  the_char->SetMoved(false);
  the_char->SetActionDone(true);
  Chase *chase = new Chase();
  Attack *atk = new Attack();
  Wait *warten = new Wait();

  AddState("BRAIINS",chase);
  AddState("NOMNOM!!!",atk);
  AddState("STAY",warten);
}

Zombie_AI::Zombie_AI(BaseCharacter* the_char, AIState* starting_state): AIEntity (the_char,starting_state)
{
  the_char->SetMoved(false);
  the_char->SetActionDone(true);

  Chase *chase = new Chase();
  Attack *atk = new Attack();
  Wait *warten = new Wait();

  AddState("BRAIINS",chase);
  AddState("NOMNOM!!!",atk);
  AddState("STAY",warten);
}

void Zombie_AI::Update()
{
 
  if(cur_state!=NULL && target!=NULL)
    {
      
      pair<int,int> current_pair(getCharacter()->getPosition().x/TILE_SIZE,getCharacter()->getPosition().y/TILE_SIZE);
      
      //if our target isnt dead and we can see him
      if( (target->getState() != STATE_DEAD && target->getState()!=STATE_DYING)  &&
	  MapIndex::Instance()->RayTrace(current_pair.second,current_pair.first,target->getPosition().y/TILE_SIZE,target->getPosition().x/TILE_SIZE))
	{
	  
	  if(ActionFinished())
	    {
	      pair<int,int> up( target->getPosition().x/TILE_SIZE,target->getPosition().y/TILE_SIZE -1);
	      pair<int,int> down( target->getPosition().x/TILE_SIZE,target->getPosition().y/TILE_SIZE +1);
	      pair<int,int> left( target->getPosition().x/TILE_SIZE -1,target->getPosition().y/TILE_SIZE);
	      pair<int,int> right( target->getPosition().x/TILE_SIZE +1,target->getPosition().y/TILE_SIZE);
	      //move towards him
	      if(!the_char->Moved())
		{ 
		  ChangeState("BRAIINS");
		  the_char->SetMoved(true);
		  cur_state->Execute(this);
		  return;
		}
	      //double move or attack
	      if(!the_char->ActionDone())
		{
		  
		  if(current_pair == up || current_pair == down || current_pair == left || current_pair == right)
		    {
		      ChangeState("NOMNOM!!!");
		    }
		  else
		    {
		      ChangeState("BRAIINS");
		    }
		  the_char->SetActionDone(true);
		  cur_state->Execute(this);
		  return;
		}
	    }
	}
      else
	{
	  ChangeState("STAY");
	  the_char->SetMoved(true);
	  the_char->SetActionDone(true);
	}
    }
  else
    {
      ChangeState("STAY");
      the_char->SetMoved(true);
      the_char->SetActionDone(true);
    }
}
void Zombie_AI::setTarget(BaseCharacter *target)
{
  this->target = target;
  ((Chase*) getState("BRAIINS"))->setTarget(target);
  ((Attack*) getState("NOMNOM!!!"))->setTarget(target);
  ChangeState("BRAIINS");



}

