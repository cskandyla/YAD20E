#include "Doodad.h"
#ifndef __DOODAD_FUNCS__
#define __DOODAD_FUNCS__

struct DoodadFunction_Entry
{
  const char* doodfunc_name;
  DoodadFunction Doodadfunc;
  
};

extern DoodadFunction_Entry DoodadFunctions[];
int LookUpDoodadFunction(const char *doodfunc_name);

//ActualFunctions
void DoorOpen(Doodad *doodad);
void DoorClose(Doodad *doodad);

void DoubleDoorOpen(Doodad *Doodad);
void DoubleDoorClose(Doodad *Doodad);


#endif
