#include "Stats.h"
#include "SpellEffects.h"
#include <string>


#ifndef __EFFECT_H
#define __EFFECT_H

class BaseCharacter;
class Effect
{
private:
    int Duration;//NUM OF TURNS THE EFFECT LASTS
    int numApplications;//NUMBER OF TIMES EFFECT IS APPLIED (ONCE EACH TURN) FOR num TURNS
    bool Permanent;
    std::string Name;
    Spell_Effect_t effect_;
    SpellStats *sp_stats;

public:
    Effect(std::string name,int duration,int numOfEffectApplications,bool Permanent,    Spell_Effect_t effect,SpellStats *sp_stats);
    virtual ~Effect();
    void ApplyEffect();
    void RemoveEffect();
    void Reduceduration();
    int getDuration()
    {
        return Duration;
    }
    bool IsPermanent()
    {
        return Permanent;
    }
    void PrintStats();
    std::string getName()
    {
        return Name;
    }
};
//LUA


#endif // __EFFECT_H
