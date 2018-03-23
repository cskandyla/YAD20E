
#include "AIEntity.h"

#ifndef __BRAIIIINS__
#define __BRAIIIINS__

class Zombie_AI : public AIEntity
{
private:
    BaseCharacter *target;
public:
    Zombie_AI(BaseCharacter *the_char);
    Zombie_AI(BaseCharacter *the_char,AIState *starting_state);
    void Update();
    void setTarget(BaseCharacter *target);
};

#endif // __BRAIIIINS__
