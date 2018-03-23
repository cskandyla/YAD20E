#include "Effect.h"
#include <iostream>
#include <string>
using namespace std;

Effect::Effect(std::string name,int duration,int numOfEffectApplications,bool Permanent,    Spell_Effect_t effect,SpellStats *sp_stats)
{

  this->Name=name;
  this->Duration=duration;
  this->numApplications=numOfEffectApplications;
  this->Permanent=Permanent;
  this->effect_=effect;
  this->sp_stats=sp_stats;
}

Effect::~Effect()
{
  delete sp_stats;
}

void Effect::ApplyEffect()
{


    if(Duration>0 && numApplications >0)
    {
      if(effect_!=NULL)
      effect_(sp_stats);
        numApplications--;
    }
    Duration--;
}
void Effect::RemoveEffect()
{
    if(!Permanent && numApplications==0)
      {
	//foo bar
      }
}

void Effect::Reduceduration()
{
    Duration--;
    numApplications--;
}




void Effect::PrintStats()
{
    cout<<Duration<<endl;
    cout<<numApplications<<endl;
    cout<<Permanent<<endl;

}



