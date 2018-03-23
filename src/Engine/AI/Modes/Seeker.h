

#include "AIEntity.h"

#ifndef __FIND_A_NICE_SPOT__
#define __FIND_A_NICE_SPOT__

class Seeker_AI : public AIEntity
{
private:
    BaseCharacter *target;
public:
    Seeker_AI(BaseCharacter *the_char);
    Seeker_AI(BaseCharacter *the_char,AIState *starting_state);
    void Update();
    void setTarget(BaseCharacter *target);
};

#endif // __FIND_A_NICE_SPOT__
