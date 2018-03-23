#include "LineSpell.h"
#include "Caster.h"
#include "BaseRenderer.h"

LineSpell::LineSpell(SpellInfo *spell_info,BaseCharacter *caster,void (*Effect)(SpellStats *sp_stats),AnimatedEntity *spell_entity): IncrementingSpell(spell_info,caster,Effect,spell_entity)
{
}

LineSpell::~LineSpell()
{
  
}

void LineSpell::Draw(SDL_Texture *screen)
{
  //cout<<"Increment"<<increment<<endl;
  int anim_width=7;
  int tile_size=MapIndex::Instance()->getMap()->getTileSize();
  int chunks=increment/tile_size;
  
  for(int i=0;i<chunks;i++)
    {
      if(GetSpellStats()->GetDirection()==S_LEFT)
	{
	  spell_entity->DrawAt(-i*tile_size,-tile_size+tile_size/4,screen);
	}
      else if(GetSpellStats()->GetDirection()==S_RIGHT)
	{
	  spell_entity->DrawAt(i*tile_size,-tile_size+tile_size/4,screen);
	}
      else if(GetSpellStats()->GetDirection()==S_UP)
	{
	  spell_entity->DrawAt(0,i*tile_size-tile_size/2,screen); 
	}
      else if(GetSpellStats()->GetDirection()==S_DOWN)
	{
	  spell_entity->DrawAt(0,i*tile_size-tile_size/2,screen); 
	}
    }
}
void LineSpell::OnCast()
{
  spell_entity->setAnimation(0);
  spell_entity->setPosition(sp_stats->GetTarget().first,sp_stats->GetTarget().second+spell_entity->getPosition().h/2);
}
