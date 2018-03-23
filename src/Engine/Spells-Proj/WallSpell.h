#include "EOTSpell.h"

#ifndef __WALLSPELL__
#define __WALLSPELL__

//length=radius, orientation by req target//hack
class WallSpell : public EOTSpell
{
 private:
  bool wall_built;
  void (*BuiltEffect)(SpellStats *sp_stats);
  void (*ExpiredEffect)(SpellStats *sp_stats);
public:
  WallSpell(SpellInfo *spell_info,BaseCharacter *caster,void (*Effect)(SpellStats *sp_stats),AnimatedEntity *spell_entity,int duration,
	    void (*BuiltEffect)(SpellStats *sp_stats),void (*ExpiredEffect)(SpellStats *sp_stats));
  WallSpell(const WallSpell &aspell);
  
  virtual void Update(float time);
  virtual void Draw(SDL_Texture *screen);
  virtual void OnCast();
  virtual void OnDone();

};

#endif
