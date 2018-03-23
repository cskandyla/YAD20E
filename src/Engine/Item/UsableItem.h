#include <utility>
using std::pair;
#include "Item.h"
#include "SpellEffects.h"
#include "Stats.h"
#ifndef __USABLEITEM_H_
#define __USABLEITEM_H_

class UsableItem:public Item
{
 private:
  SpellStats *sp_stats;
  Spell_Effect_t effect;
 public:
  UsableItem(ItemInfo *info,Stats *BaseStats,SDL_Texture *itemtex,Spell_Effect_t effect,SpellStats *sp_stats);
  virtual ~UsableItem();
  void Use(pair<int,int> target);
  
};

#endif

