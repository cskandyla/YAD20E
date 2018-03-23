#include "Die.h"
#include <cstdlib>
#include <ctime>


#ifndef __DIE
#define __DIE

int  Die::Roll(int BaseDie,int NumRolls)
{

    int totalRoll=0;
    for(int i=0; i<NumRolls; i++)
    {
        totalRoll+=(rand()%BaseDie + 1 );


    }


    return totalRoll;
}

#endif
