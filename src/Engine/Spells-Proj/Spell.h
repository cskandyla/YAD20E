#include <vector>
#include <string>
#include <SDL2/SDL.h>
#include "Info.h"
#include "Stats.h"
#include "BasicCharacter.h"
#include "MapIndex.h"
using std::vector;
using std::string;

#ifndef __SPELL_H
#define __SPELL_H

//TYPEDEF AND NECCESSARY TYPES DEFINITIONS 


class CellInfo;
class Spell
{
 private:
  bool Done;
  bool Cast;
 protected:
  SpellInfo *spell_info;
  SpellStats *sp_stats;
  BaseCharacter *caster;
  void (*Effect)(SpellStats *sp_stats);
  SDL_Texture *icon;
 public:
  Spell(SpellInfo *spell_info,BaseCharacter *caster,void (*Effect)(SpellStats *sp_stats));
  Spell(const Spell &aspell);
  virtual ~Spell(); //Free everything
  
  virtual void Update(float time)=0;
  virtual void Draw(SDL_Texture *screen)=0;
  virtual void Reset()=0;
  virtual void OnCast()=0;
  virtual void OnDone()=0;
  bool CastSpell();
  bool IsValidTarget();
  bool IsCast();
  void SetCast(bool cast);
  SpellInfo*  GetSpellInfo();
  SpellStats* GetSpellStats();
  void SetSpellStats(SpellStats* sp_stats);
  BaseCharacter* GetCaster();
  void SetCaster(BaseCharacter *caster);
  void SetDone(bool Done);
  bool IsDone();
  void LoadIcon(SDL_Texture *icon);
  SDL_Texture* GetIcon();
  void SetDirection(DIRECTION dir);

};

#endif
