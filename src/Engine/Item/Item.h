#include "Info.h"
#include "Stats.h"
#include "Effect.h"
#include "miscellaneous.h"
#include <SDL2/SDL.h>
#include <list>
#include <string>
#include <iostream>
using std::list;
using std::string;
using std::cout;
using std::endl;
#ifndef __ITEM__
#define __ITEM__

class Item
{
protected:
    ItemInfo *info;
    Stats *Basestats;
    Stats *currentstats;
    list<Effect*> item_effects;
    SDL_Texture *itemimage;
    SDL_Rect position;
    int id;
public:
    Item(ItemInfo *info,Stats *BaseStats,SDL_Texture *itemtex);
    virtual ~Item();
    SDL_Texture* getIcon();
    void SetPosition(int x,int y);
    void Show(SDL_Texture *screen);
    void setID(int id);
    int getID();
    ItemInfo* getInfo();
    SDL_Rect getPosition()
    {
        return position;
    }
};


#endif // __ITEM__
