#include "Weapon.h"


Weapon::Weapon(WeaponInfo* info, Stats* BaseStats, SDL_Texture *itemtex, AnimatedEntity* itementity):VisibleItem(info,BaseStats,itemtex,itementity)
{

}


WeaponInfo* Weapon::getInfo()
{
    WeaponInfo *winfo=dynamic_cast<WeaponInfo*>(this->info);
    if(winfo!=NULL)
        return winfo;
    else return NULL;
}
