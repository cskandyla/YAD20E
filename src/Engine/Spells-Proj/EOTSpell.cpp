#include "EOTSpell.h"
#include "Caster.h"

EOTSpell::EOTSpell(SpellInfo *spell_info,BaseCharacter *caster,void (*Effect)(SpellStats *sp_stats),AnimatedEntity *spell_entity,int duration)
  :Spell(spell_info,caster,Effect),spell_entity(spell_entity),duration(duration),orig_duration(duration)
{
  
}

EOTSpell::EOTSpell(const EOTSpell &aspell):Spell(aspell)
{
  this->orig_duration=aspell.orig_duration;
  this->duration=aspell.duration;
  this->spell_entity=new AnimatedEntity(*aspell.spell_entity);
}

EOTSpell::~EOTSpell()
{
  delete spell_entity;
}


void EOTSpell::Reset()
{
  duration=orig_duration;
}

void EOTSpell::OnCast()
{
  cout<<"OnCast"<<endl;
}

void EOTSpell::Draw(SDL_Texture *screen)
 {
   if(duration>0 && IsCast())
   spell_entity->Draw(screen);
 }

void EOTSpell::Update(float time)
{
  if(IsCast() && duration>0)
  spell_entity->Update(time);
}

void EOTSpell::OnDone()
{
  SetCast(false);
}

void EOTSpell::Trigger()
{
  cout<<"Triggering"<<endl;
  Effect(sp_stats);
  duration--;
}

void EOTSpell::SetDuration(int duration)
{
  this->duration=duration;
}
int EOTSpell::GetDuration()
{
  return this->duration;
}
