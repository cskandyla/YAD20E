#include "VisibleItem.h"

VisibleItem::VisibleItem(ItemInfo *info,Stats *BaseStats,SDL_Texture *itemtex,AnimatedEntity *itementity):Item(info,BaseStats,itemtex)
{

    this->itementity=itementity;
}

VisibleItem::~VisibleItem()
{
  delete itementity;
}

void VisibleItem::Draw(SDL_Texture *screen)
{
    this->itementity->Draw(screen);
}

void VisibleItem::Update(float t)
{
    this->itementity->Update(t);
}

void VisibleItem::setAnimation(ANIMS anim)
{
    this->itementity->setAnimation(anim);
}

void VisibleItem::SetDestination(int x,int y)
{
    this->itementity->SetDestination(x,y);
}
SDL_Rect VisibleItem::getPosition()
{
    return this->itementity->getPosition();
}

void VisibleItem::setPosition(int x,int y)
{
    this->itementity->setPosition(x,y);
}

void VisibleItem::SetVelocity(int x,int y)
{
    this->itementity->SetVelocity(x,y);
}

AnimatedEntity* VisibleItem::getEntity()
{


  return itementity;


}
