#include "Spell.h"
#include "Distances.h"

Spell::Spell(SpellInfo *spell_info,BaseCharacter *caster,void (*Effect)(SpellStats *sp_stats)):spell_info(spell_info),caster(caster)
{

  this->Effect=Effect;
  this->sp_stats=NULL;
  this->Done=false;
  this->Cast=false;
  icon=NULL;
}

Spell::Spell(const Spell &aspell)
{
  
  this->Effect=aspell.Effect;
  this->spell_info=new SpellInfo(aspell.spell_info->getName(),aspell.spell_info->getClass(),aspell.spell_info->getSchool(),aspell.spell_info->getDescription());
  this->caster=aspell.caster;


  this->sp_stats=new SpellStats(aspell.sp_stats->GetRange(),aspell.sp_stats->GetRadius(),aspell.sp_stats->GetMastery(),
				aspell.sp_stats->GetLevel(), aspell.sp_stats->GetAoeType(),aspell.sp_stats->GetTarget(),aspell.sp_stats->GetTargetReq(),
				aspell.sp_stats->GetDirection());
  this->Done=aspell.Done;
  this->Cast=aspell.Cast;
  //this->icon=aspell.icon;->need to use a resource manager 
}


Spell::~Spell()
{
  delete spell_info;
  delete sp_stats;
  if(icon)
    SDL_DestroyTexture(icon);
}


BaseCharacter* Spell::GetCaster()
{
  return this->caster;
}

void Spell::SetCaster(BaseCharacter *caster)
{
  this->caster=caster;
}

void Spell::SetDone(bool Done)
{
  if(Done==true)
    OnDone();
  this->Done=Done;
}

bool Spell::IsDone()
{
  return this->Done;
}

SpellStats* Spell::GetSpellStats()
{
  return this->sp_stats;
}

SpellInfo* Spell::GetSpellInfo()
{
  return this->spell_info;
}

void Spell::SetSpellStats(SpellStats* sp_stats)
{
  this->sp_stats=sp_stats;
}

bool Spell::IsValidTarget()
{

  pair<int,int> caster_pos(sp_stats->GetTarget().first/TILE_SIZE,sp_stats->GetTarget().second/TILE_SIZE);
  pair<int,int>target_pos(caster->GetBaseEntity()->getPosition().x/TILE_SIZE,caster->GetBaseEntity()->getPosition().y/TILE_SIZE);

  if(!MapIndex::Instance()->RayTrace(caster_pos.second,caster_pos.first,target_pos.second,target_pos.first))
    {
      return false;
    }
  
  if(sp_stats->GetTargetReq() && MapIndex::Instance()->getCell(sp_stats->GetTarget().second/TILE_SIZE,sp_stats->GetTarget().first/TILE_SIZE)==NULL)
	{
	  caster->setState(STATE_STAND);
	  return false;
	}

  int dist=Distances::Manhattan_Distance(caster_pos,target_pos);
   cout<<"Distance To Target:"<<dist<<endl;
  if(sp_stats->GetRange()<dist)
    {
      
      return false;
    }
  return true;
}

bool Spell::CastSpell()
{
  //We require a valid target

  if(IsValidTarget())
    {
      OnCast();
      this->Cast=true;
      return true;
    }
  return false;
  
}

void Spell::SetCast(bool cast)
{
  this->Cast=cast;
}

bool Spell::IsCast()
{
  
  return this->Cast;
}

void Spell::LoadIcon(SDL_Texture *icon)
{
  this->icon=icon;
}

SDL_Texture* Spell::GetIcon()
{
  return this->icon;
}

void Spell::SetDirection(DIRECTION dir)
{
  if(dir==UP)
    {
      sp_stats->SetDirection(S_UP);
    }
  else   if(dir==DOWN)
    {
      sp_stats->SetDirection(S_DOWN);
    }
  else   if(dir==LEFT)
    {
      sp_stats->SetDirection(S_LEFT);
    }
  else   if(dir==RIGHT)
    {
      sp_stats->SetDirection(S_RIGHT);
    }
}
