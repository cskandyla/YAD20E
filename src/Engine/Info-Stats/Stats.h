#include <utility>
#include <string>
using std::pair;
#ifndef __STATS__
#define __STATS__

class Stats
{
 private:
  int Int,Dex,Str,Con;//BASE STATS//
  int Hp,Def,Dmg,ToHit,Speed;//DEPENDANT STATS
  bool canMove,canCast,canAttack,prone;
  void UpdateStats();
 public:
  Stats(int Str,int Dex,int Int,int Con);
  Stats(int Str,int Dex,int Int,int Con,int Hp,int Def,int Dmg,int ToHit,int Speed, bool canMove,bool canCast,bool canAttack,bool prone);
  Stats();
  int getInt()
  {
    return Int;
  }
  int getDex()
  {
    return Dex;
  }
  int getStr()
  {
    return Str;
  }
  int getCon()
  {
    return Con;
  }
  int getHp()
  {
    return Hp;
  }
  int getDef()
  {
    return Def;
  }
  int getDmg()
  {
    return Dmg;
  }
  int getToHit()
  {
    return ToHit;
  }
  int getSpeed()
  {
    return Speed;
  }
  void SetHp(int hp)
  {
    this->Hp=hp;
  }
  bool CanMove()
  {
    return canMove;
  }
  bool CanCast()
  {
    return canCast;
  }
  bool CanAttack()
  {
    return canAttack;
  }
  bool Prone()
  {
    return prone;
  }

  int getStat(const char  *stat);
  void setStat(const char *stat,int value);
  void PrintStats();
  void Apply(Stats *s);
  void Remove(Stats *s);
};


class Attributes
{
 private:
  int Strength,Dexterity,Constitution,Intelligence,Spirit;

 public:
  Attributes(int str,int dex,int con,int iint,int spi);
  void SetStr(int str);
  void SetDex(int dex);
  void SetCon(int Con);
  void SetInt(int iint);
  void SetSpi(int spi);
  int getStr();
  int getDex();
  int getCon();
  int getInt();
  int getSpi();
};

class GeneralStats
{
 private:
  int HealthPoints,Speed,Experience;
  bool canMove,canCast,canAttack;
 public:
  GeneralStats(int hp,int sp,int xp);
  GeneralStats(int hp,int sp,int xp,bool CM,bool CC,bool CA);
  void SetHp(int hp);
  void SetSpeed(int speed);
  void SetXp(int xp);
  int getHp();
  int getSpeed();
  int getXp();
  int getLevel();
  bool CanCast();
  bool CanMove();
  bool CanAttack();
  void SetCast(bool cast);
  void SetMove(bool move);
  void SetAttacK(bool attack);

};

class CombatStats
{
 private:
  int BaseAttackBonus,ToHitBonus,Damage,ArmorClass,SpellResistance;
 public:
  CombatStats(int BAB,int tohit,int Dmg,int AC,int SR);
  int getBAB();
  int getTohitBonus();
  int getDamage();
  int getArmorClass();
  int getSR();
  void SetBAB(int BAB);
  void SetToHitBonus(int tohit);
  void SetDamage(int dmg);
  void SetArmorClass(int ac);
  void SetSR(int sr);
};



enum AOE{SINGLE=0,MULTIPLE,DISK,CONE,CLOUD,LINE,WALL};
enum SPELL_DIRECTION{S_NONE=0,S_UP,S_RIGHT,S_LEFT,S_DOWN};
class SpellStats
{
 private:
  int range;
  int radius;
  int mastery;
  int level;
  AOE aoe_type;
  bool requires_target;
  SPELL_DIRECTION dir;
  pair<int,int> target;  
 public:
  SpellStats(int range,int radius,int mastery,int level,AOE aoe_type,pair<int,int> target,bool target_req);
  SpellStats(int range,int radius,int mastery,int level,AOE aoe_type,pair<int,int> target,bool target_req,SPELL_DIRECTION dir);
  SpellStats(int range,int radius,int mastery,int level,AOE aoe_type,bool target_req);
  int  GetRange();
  int  GetRadius();
  int  GetMastery();
  int  GetLevel();
  AOE  GetAoeType();
  bool GetTargetReq();
  SPELL_DIRECTION GetDirection();
  pair<int,int> GetTarget();
  void SetRange(int range);
  void SetRadius(int radius);
  void SetMastery(int mastery);
  void SetLevel(int level);
  void SetAoeType(AOE aoe_t);
  void SetTarget(pair<int,int> target);
  void SetTargetReq(bool target_req);
  void SetDirection(SPELL_DIRECTION dir);
};

enum SPELL_SCHOOL
  {    ABJURATION=0,
       CONJURATION,
       DIVINATION,
       ENCHANTMENT,
       EVOCATION,
       ILLUSION,
       NECROMANCY,
       TRANSMUTATION
  };

enum SPELL_SCHOOL school_string_to_enum(std::string school_name);

class CasterStats
{
 private:
  int spell_slots[6][10];//vector<vector<int>>?
  int mastery[8];//vector<vector<int>>?
 public:
  CasterStats(int spell_slots[6][10],int mastery[8]);

  void SetSpellSlots(int char_level,int spell_level,int slots);
  void SetMastery(enum SPELL_SCHOOL school,int rankz);
  void SetMastery(int school,int rankz);
  
  int GetSpellSlots(int char_level,int spell_level);
  int GetMastery(enum SPELL_SCHOOL school);
  int GetMastery(int school);
};


#endif
