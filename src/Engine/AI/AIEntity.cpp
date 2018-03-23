#include "AIEntity.h"
#include "State_Attack.h"
#include <iostream>




AIEntity::AIEntity(BaseCharacter *the_char):the_char(the_char)
{
    this->cur_state=NULL;
    the_char->SetMoved(false);
    the_char->SetActionDone(false);

}

AIEntity::AIEntity(BaseCharacter* the_char, AIState* starting_state):the_char(the_char),cur_state(starting_state)
{
    the_char->SetMoved(false);
    the_char->SetActionDone(false);
}

AIEntity::~AIEntity()
{
  std::unordered_map<string,AIState*>::iterator it;
  for(it=states.begin();it!=states.end();++it)
    {
      delete it->second;
    }
}

bool AIEntity::ActionFinished()
{
  if(the_char->getState() == STATE_STAND && (!the_char->getProjectile() || !the_char->getProjectile()->IsActive()))
    {
        //std::cout<<"Stands"<<std::endl;
        return true;
    }
    return false;
}


void AIEntity::AddState(string name,AIState* state)
{

    states[name]=state;

}

AIState* AIEntity::getState(string state)
{
    if(states.find(state)!=states.end())
    {
        return states[state];
    }
    return NULL;
}


void AIEntity::Update()
{
    if(the_char->getState() == STATE_STAND)
        cur_state->Execute(this);
}





void AIEntity::ChangeState(AIState* state)
{
    cur_state=state;
}


void AIEntity::ChangeState(string state)
{
    if(states.find(state)!=states.end())
    {
        cur_state=states[state];
    }
}



BaseCharacter* AIEntity::getCharacter()
{
    return this->the_char;
}



bool AIEntity::TurnDone()
{
  if(the_char->Moved() && the_char->ActionDone() && ActionFinished())
    {
      MapIndex::Instance()->CharIndexUpdate(getCharacter(),0,0);
      return true;
    }
    return false;

}



void AIEntity::Reset()
{
  

}
