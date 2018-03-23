#include "CharacterState.h"
#ifndef __WARRIOR_STATES_H
#define __WARRIOR_STATES_H


#define STATE_CLEAVE 7
#define STATE_KNOCKDOWN 8
#define STATE_EXPERTSTRIKE 9
class WarriorReaction:public CharacterState
{
public:
  WarriorReaction(CharacterHandler *s_handler);
  virtual void Execute();
};

#endif
