#include "WallSpell.h"
#include "Caster.h"
#include "MapIndex.h"

WallSpell::WallSpell(SpellInfo *spell_info,BaseCharacter *caster,void (*Effect)(SpellStats *sp_stats),AnimatedEntity *spell_entity,int duration,
		     void (*BuiltEffect)(SpellStats *sp_stats),void (*ExpiredEffect)(SpellStats *sp_stats))
  :EOTSpell(spell_info,caster,Effect,spell_entity,duration)
{
  this->BuiltEffect=BuiltEffect;
  this->ExpiredEffect=ExpiredEffect;
  wall_built=false;
}

WallSpell::WallSpell(const WallSpell &aspell):EOTSpell(aspell)
{
  this->wall_built=aspell.wall_built;
  this->BuiltEffect=aspell.BuiltEffect;
  this->ExpiredEffect=aspell.ExpiredEffect;
}

void WallSpell::OnCast()
{
  cout<<"WallSpell OnCast"<<endl;
  if(sp_stats)
    {
       if(GetSpellStats()->GetDirection()==S_UP || GetSpellStats()->GetDirection()==S_DOWN)
	    spell_entity->setAnimation(2);
	  else
	    spell_entity->setAnimation(0);
      spell_entity->setPosition(sp_stats->GetTarget().first,sp_stats->GetTarget().second+spell_entity->getPosition().h/2);
      spell_entity->setAnimLoop(NO);
      Reset();
    }
}

void WallSpell::Draw(SDL_Texture *screen)
{
  int tile_size=MapIndex::Instance()->getMap()->getTileSize();
  if(duration>0 && IsCast())
    {
      for(int i=-GetSpellStats()->GetRadius()+1;i<GetSpellStats()->GetRadius();i++)
	{
	  if( (GetSpellStats()->GetDirection()==S_LEFT || GetSpellStats()->GetDirection()==S_RIGHT )   )
	    {
	      spell_entity->DrawAt(i*tile_size,-tile_size+tile_size/2,screen);
	    }
	  else if( (GetSpellStats()->GetDirection()==S_UP || GetSpellStats()->GetDirection()==S_DOWN )  )
	    {
	      spell_entity->DrawAt(0,i*tile_size-tile_size/2,screen); 
	    }
	}
      
    }
}

void WallSpell::Update(float time)
{
  if(IsCast() && duration>0)
    {
      if(!wall_built && spell_entity->getCur_Anim()->Done())
	{
	  wall_built=true;
	  if(GetSpellStats()->GetDirection()==S_UP || GetSpellStats()->GetDirection()==S_DOWN)
	    spell_entity->setAnimation(3);
	  else
	    spell_entity->setAnimation(1);
	  spell_entity->setPosition(sp_stats->GetTarget().first,sp_stats->GetTarget().second+spell_entity->getPosition().h/2);
	  spell_entity->setAnimLoop(YES);
	  //we're adding it each round?
	  BuiltEffect(sp_stats);
	  Caster *the_caster=dynamic_cast<Caster*>(caster);
	  the_caster->AddEOTSpell(new WallSpell(*this));
	}
      spell_entity->Update(time);
    }
  if(duration==0)
    {
      ExpiredEffect(sp_stats);
    }
}

void WallSpell::OnDone()
{
  SetCast(false);
  wall_built=false;
  Reset();
}
