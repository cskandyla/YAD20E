#include "Armor.h"
Armor::Armor(ArmorInfo* info, Stats* BaseStats, SDL_Texture *itemtex, AnimatedEntity* itementity):VisibleItem(info,BaseStats,itemtex,itementity)
{

}

Armor::~Armor()
{
  cout<<"Armor"<<endl;
}


ArmorInfo* Armor::getInfo()
{
    ArmorInfo *ainfo=dynamic_cast<ArmorInfo*>(this->info);
    if(ainfo!=NULL)
        return ainfo;
    else return NULL;
}
