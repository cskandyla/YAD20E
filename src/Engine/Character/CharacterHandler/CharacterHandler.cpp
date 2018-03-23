#include "CharacterHandler.h"

CharacterHandler::CharacterHandler(BaseCharacter *the_char):the_char(the_char)
{
  cur_state=NULL;
}

void CharacterHandler::AddState(int statenum,CharacterState *state)
{
  if(states.find(statenum)==states.end())
    {
      states[statenum]=state;
    }
}

void CharacterHandler::SetState(int state)
{
  if(states.find(state)!=states.end())
    {
      this->state=state;
      cur_state=states[state];
    }
}
int CharacterHandler::GetCurrentStateNum()
{
  return state;
}
void CharacterHandler::Update()
{
  if(cur_state)
    cur_state->Execute();
}


BaseCharacter* CharacterHandler::GetTheCharacter()
{
  return the_char;
}
