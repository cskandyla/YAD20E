#include "Item.h"
#include "BaseRenderer.h"

Item::Item(ItemInfo *info,Stats *BaseStats,SDL_Texture *itemtex)
{
    this->info=info;
    this->Basestats=BaseStats;

    cout<<info->getName()<<endl;
    this->itemimage=itemtex;
    //SDL_FreeSurface(oldsurf);
    if(itemimage==NULL)
    {
        cout<<"Loading "<<" failed"<<endl;
    }
    position.x=0;
    position.y=0;
    id=-1;
}

Item::~Item()
{
  cout<<"Freeing image"<<endl;
  if(itemimage)
    SDL_DestroyTexture(itemimage);
  cout<<"Deleting Stats and Info"<<endl;
  delete info;
  delete Basestats;
  //  delete currentstats;
  cout<<"Deleting Effects"<<endl;
  list<Effect*>::iterator it;
  for(it=item_effects.begin();it!=item_effects.end();++it)
    {
      delete *it;
    }
  
}

void Item::setID(int id)
{
  this->id=id;
}
int Item::getID()
{
  return this->id;
}


SDL_Texture* Item::getIcon()
{
        return itemimage;
}

ItemInfo* Item::getInfo()
{
    return this->info;
}

void Item::SetPosition(int x,int y)
{
    this->position.x=x;
    this->position.y=y;
}
void Item::Show(SDL_Texture *screen)
{
    if(itemimage!=NULL)
    BaseRenderer::Instance()->RenderTexture(itemimage,screen,NULL,&position);
}
