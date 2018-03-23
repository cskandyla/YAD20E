#include "State.h"
#include "BasicCharacter.h"
#include "AIEntity.h"

#ifndef __STATE_CHASE__
#define __STATE_CHASE__


class Chase : public AIState
{
private:
    BaseCharacter *target;
public:
    Chase();
    void Execute(AIEntity *the_char);
    void setTarget(BaseCharacter *target);


};
#endif // __STATE_CHASE__
