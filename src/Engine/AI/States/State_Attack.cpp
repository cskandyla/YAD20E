#include "State_Attack.h"


Attack::Attack()
{


}

void Attack::Execute(AIEntity *the_char)
{
    if(target != NULL)
        the_char->getCharacter()->Attack(target);
}

void Attack::setTarget(BaseCharacter *t)
{
    target = t;
}
