#include "State.h"
#include "AIEntity.h"
#include "BasicCharacter.h"

#ifndef __STATE_ATTACK__
#define __STATE_ATTACK__


class Attack : public AIState
{
private:
    BaseCharacter *target;
public:
    Attack();
    void Execute(AIEntity *the_char);
    void setTarget(BaseCharacter *target);


};
#endif // __STATE_ATTACK__
