#include "VisibleItem.h"


#ifndef __ARMOR__
#define __ARMOR__
class Armor:public VisibleItem
{
public:
    Armor(ArmorInfo *info,Stats *BaseStats,SDL_Texture *itemtex,AnimatedEntity *itementity);
    virtual ~Armor();
    ArmorInfo* getInfo();
};

#endif
