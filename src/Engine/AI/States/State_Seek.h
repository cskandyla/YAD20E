#include "State.h"
#include "BasicCharacter.h"
#include "AIEntity.h"
#ifndef __STATE_SEEK__
#define __STATE_SEEK__


class Seek : public AIState
{
private:
    BaseCharacter *target;
public:
    Seek();
    void Execute(AIEntity *the_char);
    void setTarget(BaseCharacter *target);


};
#endif // __STATE_SEEK__
