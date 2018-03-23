#include "UsableItem.h"

UsableItem::UsableItem(ItemInfo *info,Stats *BaseStats,SDL_Texture *itemtex,Spell_Effect_t effect,SpellStats *sp_stats):Item(info,BaseStats,itemtex),effect(effect),sp_stats(sp_stats)
{
  
}

UsableItem::~UsableItem()
{
  delete sp_stats;
}

void UsableItem::Use(pair<int,int> target)
{
  //Just set target and user effect
  sp_stats->SetTarget(target);
  effect(sp_stats);

}
