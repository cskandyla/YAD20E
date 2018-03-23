#include "MovingEntity.h"
#include "State.h"
#include "CharacterState.h"

#include <list>
#include <unordered_map>
using std::list;
using std::unordered_map;
#ifndef __CHARACTER_HANDLER__
#define __CHARACTER_HANDLER__

//Default StateHandler for BaseCharacters 
class BaseCharacter;
class CharacterHandler
{
 private:
  BaseCharacter *the_char;
  int state;
  CharacterState *cur_state;
  unordered_map<int,CharacterState*> states;
 public:
  CharacterHandler(BaseCharacter *the_char);
  void AddState(int statenum,CharacterState *state);
  void SetState(int state);
  int GetCurrentStateNum();
  virtual void Update();
  BaseCharacter* GetTheCharacter();

};
#endif
