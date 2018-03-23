#ifndef __CHARACTERSTATE_H__
#define __CHARACTERSTATE_H__

class CharacterHandler;
class BaseCharacter;
class CharacterState
{
protected:
  BaseCharacter *the_char;
  CharacterHandler  *s_handler;
public:
  CharacterState(CharacterHandler *s_handler);
  virtual void Execute()=0;
};

class CharacterStand:public CharacterState
{
 public:
  CharacterStand(CharacterHandler *s_handler);
  virtual void Execute();
};

class CharacterMove:public CharacterState
{
public:
  CharacterMove(CharacterHandler *s_handler);
  virtual void Execute();
};

class CharacterAttack:public CharacterState
{
public:
  CharacterAttack(CharacterHandler *s_handler);
  virtual void Execute();
};

class CharacterDying:public CharacterState
{
public:
  CharacterDying(CharacterHandler *s_handler);
  virtual void Execute();
};

class CharacterDead:public CharacterState
{
public:
  CharacterDead(CharacterHandler *s_handler);
  virtual void Execute();
};

class CharacterCast:public CharacterState
{
public:
  CharacterCast(CharacterHandler *s_handler);
  virtual void Execute();
};



#endif
