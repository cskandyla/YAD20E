#include "VisibleItem.h"


#ifndef __WEAPON__
#define __WEAPON__
class Weapon:public VisibleItem
{
public:
    Weapon(WeaponInfo *info,Stats *BaseStats,SDL_Texture *itemtex,AnimatedEntity *itementity);
    WeaponInfo* getInfo();

};

#endif
