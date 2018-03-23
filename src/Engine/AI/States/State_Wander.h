#include "State.h"
#include "BasicCharacter.h"
#include "AIEntity.h"

#ifndef __STATE_WANDER__
#define __STATE_WANDER__


class Wander :public AIState
{

private:

public:
    Wander();
    void Execute(AIEntity *the_char);




};
#endif // __STATE_WANDER__
