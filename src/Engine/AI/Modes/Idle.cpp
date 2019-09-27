#include "Idle.h"
#include "State_Wait.h"

Idle_AI::Idle_AI(BaseCharacter *the_char): AIEntity(the_char)
{
    this->cur_state=NULL;
    this->target = NULL;
    the_char->SetMoved(false);
    the_char->SetActionDone(false);
    
    Wait *wait = new Wait();
    AddState("STOP",wait);
    cur_state=wait;
}

Idle_AI::Idle_AI(BaseCharacter* the_char, AIState* starting_state): AIEntity (the_char,starting_state)
{
	this->cur_state=starting_state;
	this->target=NULL;
	the_char->SetMoved(false);
	the_char->SetActionDone(false);
	Wait *wait = new Wait();
	AddState("STOP",wait);
	cur_state=wait;
}



void Idle_AI::Update()
{
        //we just do nothing :D
	cur_state->Execute(this);
	the_char->SetActionDone(true);
	the_char->SetMoved(true);

}


void Idle_AI::setTarget(BaseCharacter *target)
{
    this->target = target;
}

