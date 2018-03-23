#include "CloudSpell.h"
#include "Caster.h"

CloudSpell::CloudSpell(SpellInfo *spell_info,BaseCharacter *caster,void (*Effect)(SpellStats *sp_stats),AnimatedEntity *spell_entity,int duration):EOTSpell(spell_info,caster,Effect,spell_entity,duration)
{
}

CloudSpell::CloudSpell(const CloudSpell &aspell):EOTSpell(aspell)
{
}

void CloudSpell::OnCast()
{
  cout<<"OnCast"<<endl;
  if(sp_stats)
    {
      Caster *the_caster=dynamic_cast<Caster*>(caster);
      the_caster->AddEOTSpell(this);
      spell_entity->setAnimation(0);
      spell_entity->setPosition(sp_stats->GetTarget().first,sp_stats->GetTarget().second+spell_entity->getPosition().h/2);
      spell_entity->setAnimLoop(YES);
      Reset();
      //Compute Duration and set the spell as an active spell
    }
}

void CloudSpell::Draw(SDL_Texture *screen)
 {
   if(duration>0 && IsCast())
   spell_entity->Draw(screen);
 }

void CloudSpell::Update(float time)
{
  if(IsCast() && duration>0)
  spell_entity->Update(time);
}

void CloudSpell::OnDone()
{
  SetCast(false);
}
