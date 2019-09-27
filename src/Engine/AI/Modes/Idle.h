#include "AIEntity.h"

#ifndef __I__JUST_SIT_AROUND__
#define __I__JUST_SIT_AROUND__

class Idle_AI : public AIEntity
{
private:
    BaseCharacter *target;
public:
    Idle_AI(BaseCharacter *the_char);
    Idle_AI(BaseCharacter *the_char,AIState *starting_state);
    void Update();
    void setTarget(BaseCharacter *target);
};

#endif // __FIND_A_NICE_SPOT__
