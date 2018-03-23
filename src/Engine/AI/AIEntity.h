#include "BasicCharacter.h"
#include "MapIndex.h"
#include "State.h"
#include <string>
#include <unordered_map>

using std::string;


#ifndef __AIENTITY__
#define __AIENTITY__


class AIState;
class AIEntity
{

 private:
    std::unordered_map<string,AIState*> states;
 protected:
    AIState *cur_state;
    BaseCharacter *the_char;

 public:
    AIEntity(BaseCharacter *the_char);
    AIEntity(BaseCharacter *the_char,AIState *starting_state);
    virtual ~AIEntity();
    void AddState(string name,AIState *state);
    AIState* getState(string name);
    void ChangeState(string state_name);
    void ChangeState(AIState* state);

    virtual void Update();
    BaseCharacter* getCharacter();
    bool ActionFinished();
    void Reset();
    bool TurnDone();


};

#endif // __AIENTITY__
