#include "State.h"
#include "BasicCharacter.h"
#include "AIEntity.h"
#ifndef __STATE_WAIT__
#define __STATE_WAIT__


class Wait : public AIState
{
private:

public:
    Wait();
    void Execute(AIEntity *the_char);



};
#endif // __STATE_WAIT__


