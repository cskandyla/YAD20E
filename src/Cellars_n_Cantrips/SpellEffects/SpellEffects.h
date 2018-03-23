#include "Stats.h"
#ifndef __SPELL_EFFECTS__
#define __SPELL_EFFECTS__

typedef   void (*Spell_Effect_t)(SpellStats *sp_stats);
struct SpellEffect
{
  const char* spell_name;
  Spell_Effect_t spell_effect;
  
};
//EXTERN TO REGISTER/LOOK-UP SPELL EFFECTS 
extern SpellEffect spellarchives[];
int LookUpSpell(const char *spell_name);



//Effects of Spells to hook function pointers
void ArcaneBlastEffect(SpellStats *sp_stats);
void MageArmorEffect(SpellStats *sp_stats);
void IceShardEffect(SpellStats *sp_stats);
void DeathEffect(SpellStats *sp_stats);
void FireballEffect(SpellStats *sp_stats);
void CureEffect(SpellStats *sp_stats);
void IceCageEffect(SpellStats *sp_stats);
void FlashFireEffect(SpellStats *sp_stats);
void WhirlwindEffect(SpellStats *sp_stats);
void StinkingCloudEffect(SpellStats *sp_stats);
void ForcePushEffect(SpellStats *sp_stats);
void StoneWallEffect(SpellStats *sp_stats);
void StoneWallBuiltEffect(SpellStats *sp_stats);
void StoneWallExpiredEffect(SpellStats *sp_stats);
void DisintegrationEffect(SpellStats *sp_stats);
void ConeOfColdEffect(SpellStats *sp_stats);

//Status Effects
void StunnedEffect(SpellStats *sp_stats);
void DisabledEffect(SpellStats *sp_stats);
void ShieldEffect(SpellStats *sp_stats);





#endif
