#include <utility>
#include <string>
#include <vector>
using std::string;
using std::pair;
using std::vector;


#ifndef __INPUT_STATE__
#define __INPUT_STATE__

class Camera;
class CellInfo;
class Spell;
class BaseCharacter;
class Turn;
class Item;

class InputState
{
protected:
  Turn *the_turn;
  vector<pair<int,int>> tiles;
  vector<pair<int,int>> aoe_tiles;
  bool Done;
public:
  InputState(Turn *the_turn);
  virtual void Execute(pair<int,int> pos)=0;
  vector<pair<int,int>>& GetTiles();
  vector<pair<int,int>>& GetAoeTiles();
  bool IsDone();
};

class MultiInputState : public InputState
{
 protected:
  vector<pair<int,int> > targets;
 public:
  MultiInputState(Turn *the_turn);
  //  virtual void Execute(pair<int,int> pos);
};


class SpellState: public InputState
{
 private:
  string spell;
 public:
  SpellState(Turn *the_turn,string spell);
  virtual void Execute(pair<int,int> pos);
  void BuildAoeTiles();
};

class UseState : public InputState
{
public:
	UseState(Turn *the_turn);
	virtual void Execute(pair<int,int> pos);
};

class ItemState: public InputState
{
 private:
  string item;
 public:
  ItemState(Turn *the_turn,string item);
  virtual void Execute(pair<int,int> pos);
};


class AttackState : public InputState
{
 public:
  AttackState(Turn *the_turn);
  virtual void Execute(pair<int,int> pos);
};

class MoveState : public InputState
{
 public:
  MoveState(Turn *the_turn);
  virtual void Execute(pair<int,int> pos);
  
};

class TalkState : public InputState
{
   private:
  BaseCharacter *target;
 public:
  TalkState(BaseCharacter *target);
  virtual void Execute(pair<int,int> pos);

};


#endif
