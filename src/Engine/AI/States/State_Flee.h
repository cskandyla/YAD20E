#include "State.h"
#include "BasicCharacter.h"
#include "AIEntity.h"
#ifndef __STATE_FLEE__
#define __STATE_FLEE__


class Flee : public AIState
{
private:
    BaseCharacter *target;
public:
    Flee();
    void Execute(AIEntity *the_char);
    void setTarget(BaseCharacter *target);


};
#endif // __STATE_FLEE__
