#include "IncrementingSpell.h"

IncrementingSpell::IncrementingSpell(SpellInfo *spell_info,BaseCharacter *caster,void (*Effect)(SpellStats *sp_stats),AnimatedEntity *spell_entity): Spell(spell_info,caster,Effect),spell_entity(spell_entity)
{
  increment=0;
}

IncrementingSpell::~IncrementingSpell()
{
  delete spell_entity;
}

void IncrementingSpell::Draw(SDL_Texture *screen)
{
}

void IncrementingSpell::Update(float time)
{
  //update position
  int tile_size=MapIndex::Instance()->getMap()->getTileSize();
  
  if(IsCast() && increment<GetSpellStats()->GetRadius()*tile_size)
    {//maybe fps ?
      increment+=10;
      //spell_entity->Update(time);
    }
  else if(increment>=GetSpellStats()->GetRadius()*tile_size)
    {
      Effect(sp_stats);
      OnDone();
    }
}

void IncrementingSpell::OnCast()
{
  spell_entity->setAnimation(0);
  spell_entity->setPosition(sp_stats->GetTarget().first,sp_stats->GetTarget().second+spell_entity->getPosition().h/2);
}
void IncrementingSpell::OnDone()
{
  SetCast(false);
  Reset();
}

void IncrementingSpell::Reset()
{
  increment=0;
}
