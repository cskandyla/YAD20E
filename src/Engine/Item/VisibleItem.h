
#include "Item.h"
#include "AnimatedEntity.h"

#ifndef __VISIBLEITEM__
#define __VISIBLEITEM__


class VisibleItem:public Item
{
private:
    AnimatedEntity *itementity;
public:
    VisibleItem(ItemInfo *info,Stats *BaseStats,SDL_Texture *itemtex,AnimatedEntity *itementity);
    virtual ~VisibleItem();
    void Draw(SDL_Texture *screen);
    void Update(float t);
    void setAnimation(ANIMS anim);
    void SetDestination(int x,int y);
    void setPosition(int x,int y);
    SDL_Rect getPosition();
    void SetVelocity(int x,int y);
    AnimatedEntity* getEntity();

};

#endif // __VISIBLEITEM__
