#include "InputState.h"
#include "Spell.h"
#include "Caster.h"
#include "Turn.h"
#include "Item.h"
#include "UsableItem.h"
#include "Astar.h"
#include "Camera.h"
#include "KnowledgePool.h"
InputState::InputState(  Turn *the_turn):the_turn(the_turn)
{
  Done=false;
}

vector<pair<int,int>>& InputState::GetTiles()
{
  return tiles;
}


vector<pair<int,int>>& InputState::GetAoeTiles()
{
  return aoe_tiles;
}

bool InputState::IsDone()
{
  return this->Done;
}

AttackState::AttackState(Turn *the_turn):InputState(the_turn)
{
  BaseCharacter *bchar=the_turn->TheCharacter();
  Weapon *wpn=dynamic_cast<Weapon*>(bchar->getSlot(MainWeapon));
  int radius=1;
  if(wpn)
    {
      radius=wpn->getInfo()->getRange();
    }
  int tile_size=MapIndex::Instance()->getMap()->getTileSize();
  tiles=MapIndex::Instance()->getTilesInRange(bchar->getPosition().x/tile_size,bchar->getPosition().y/tile_size,radius,true);
  aoe_tiles.push_back(pair<int,int>(0,0));
}

UseState::UseState(Turn *the_turn):InputState(the_turn)
{
	  BaseCharacter *bchar=the_turn->TheCharacter();
	  int tile_size=MapIndex::Instance()->getMap()->getTileSize();
	tiles=MapIndex::Instance()->getTilesInRange(bchar->getPosition().x/tile_size,bchar->getPosition().y/tile_size,1,false);
	    aoe_tiles.push_back(pair<int,int>(0,0));
}

void UseState::Execute(pair<int,int> pos)
{

	 if(!the_turn->StandardActionDone())
	 {
		  int tile_size=MapIndex::Instance()->getMap()->getTileSize();
		  CellInfo *cellInfo=MapIndex::Instance()->getCell(pos.second/tile_size,pos.first/tile_size);
		
		 if(cellInfo)
		 {
			 if(cellInfo->getType()==DOODAD_T)
			 {
				 MapIndex::Instance()->getDoodad(cellInfo->getID())->Trigger();
			 }
		 }
		 
	 }
	 Done=true;
}


void AttackState::Execute(pair<int,int> pos)
{
  
  if(!the_turn->StandardActionDone())
    {
      int tile_size=MapIndex::Instance()->getMap()->getTileSize();
      CellInfo *cellinfo=MapIndex::Instance()->getCell(pos.second/tile_size,pos.first/tile_size);
      if(cellinfo)
	{
	  if(cellinfo->getID()!=the_turn->TheCharacter()->getID())// If we're not clicking ourselves then: were attacking/Looting
	    {
	      BaseCharacter *opponent= KnowledgePool::Instance()->getCharacter(cellinfo->getID());
	      if(opponent)
		{
		  if(opponent->getGeneralStats()->getHp()<=0)
		    {
		      //Looting (Need Interface so...)//probably switch to another state?
		    }
		  else if( MapIndex::Instance()->RayTrace(the_turn->TheCharacter()->getPosition().y/TILE_SIZE,the_turn->TheCharacter()->getPosition().x/TILE_SIZE
							  ,opponent->getPosition().y/TILE_SIZE,opponent->getPosition().x/TILE_SIZE))
		    {
		      if(the_turn->TheCharacter()->Attack(opponent))
			the_turn->SetStandardAction(true);
		    }
		}
	    } 
	}
    }
  Done=true;
}




MoveState::MoveState(Turn *the_turn):InputState(the_turn)
{
  BaseCharacter *bchar=the_turn->TheCharacter();
  {
    int radius=bchar->GetMovementLeft();
    int tile_size=MapIndex::Instance()->getMap()->getTileSize();
    tiles=MapIndex::Instance()->getTilesInRange(bchar->getPosition().x/tile_size,bchar->getPosition().y/tile_size,radius,false);
    aoe_tiles.push_back(pair<int,int>(0,0));
  } 
}





void MoveState::Execute(pair<int,int> pos)
{
  
  if(!(the_turn->HasMoved() && the_turn->StandardActionDone()))
    {
      int tile_size=MapIndex::Instance()->getMap()->getTileSize();
      pair<int,int> cur_loc=the_turn->GetCamera()->RectToPair(the_turn->TheCharacter()->getPosition());
      pair<int,int> target_loc=pair<int,int>(pos.first/tile_size,pos.second/tile_size);
      list<DIRECTION> whole_path = AStar::getPath( MapIndex::Instance(),cur_loc,target_loc);
      if(whole_path.size()>0)
	{
	  if(whole_path.size()<=the_turn->TheCharacter()->GetMovementLeft())
	    {
		the_turn->TheCharacter()->Move(whole_path);		
		the_turn->TheCharacter()->SetMovementLeft(the_turn->TheCharacter()->GetMovementLeft()-whole_path.size());
		if(!the_turn->HasMoved() && the_turn->TheCharacter()->GetMovementLeft()<=0)
		  {
		    the_turn->SetMoved(true);
		    
		  }
		else
		  {
		    //the_turn->SetStandardAction(true);
		  }
	    }  
	}
    }
  Done=true;
}


//Pass the spellname
SpellState::SpellState(Turn *the_turn,string spell):InputState(the_turn),spell(spell)
{
  
  Caster *caster=dynamic_cast<Caster*>(the_turn->TheCharacter());
  Spell *the_spell=caster->GetSpell(spell);
  if(the_spell)
    {
      int radius=the_spell->GetSpellStats()->GetRange();
      int tile_size=MapIndex::Instance()->getMap()->getTileSize();
      //move constructor?
      tiles=MapIndex::Instance()->getTilesInRange(caster->getPosition().x/tile_size,caster->getPosition().y/tile_size,radius,true);
      BuildAoeTiles();
    }
}

void SpellState::BuildAoeTiles()
{
  Caster *caster=dynamic_cast<Caster*>(the_turn->TheCharacter());
  Spell *the_spell=caster->GetSpell(spell);
  if(the_spell)
    {
      the_spell->SetDirection(caster->GetDirection());
      int radius=the_spell->GetSpellStats()->GetRadius();
      switch(the_spell->GetSpellStats()->GetAoeType())
	{
	case SINGLE:
	  aoe_tiles.push_back(pair<int,int>(0,0));
	  break;
	case DISK:
	case CLOUD:
	  for(int y=-radius; y<=radius; y++)
	    {
	      for(int x=-radius; x<=radius; x++)
		{
		  if(x*x+y*y <= radius*radius)
		    {
		      aoe_tiles.push_back(pair<int,int>(x,y));
		    }
		}
	    }
	  break;
	case WALL:
	  for(int i=-radius+1;i<radius;i++)
	    {
	      if(the_spell->GetSpellStats()->GetDirection()==S_UP || the_spell->GetSpellStats()->GetDirection()==S_DOWN)
		{
	      aoe_tiles.push_back(pair<int,int>(0,i));
	      
		}
	      else if(the_spell->GetSpellStats()->GetDirection()==S_LEFT  || the_spell->GetSpellStats()->GetDirection()==S_RIGHT)
		{
		  aoe_tiles.push_back(pair<int,int>(i,0));
		}
	    }
	  break;
	case LINE:
	  for(int i=0;i<radius;i++)
	    {
	      if(the_spell->GetSpellStats()->GetDirection()==S_LEFT)
		{
		  aoe_tiles.push_back(pair<int,int>(-i,0));
		}
	      else if(the_spell->GetSpellStats()->GetDirection()==S_RIGHT)
		{
		  aoe_tiles.push_back(pair<int,int>(i,0));
		}
	      else if(the_spell->GetSpellStats()->GetDirection()==S_UP)
		{
		  aoe_tiles.push_back(pair<int,int>(0,-i));
		}
	      else if(the_spell->GetSpellStats()->GetDirection()==S_DOWN)
		{
		  aoe_tiles.push_back(pair<int,int>(0,i));
		}
	    }
	  
	  break;
	case CONE:
	  if( the_spell->GetSpellStats()->GetDirection()==S_UP )
	    {
	      for(int i=0;i<radius;i++)
		{
		  aoe_tiles.push_back(pair<int,int>((-1-i),(-i)));
		  for(int j=-i-1;j<i;j++)
		    {
		      aoe_tiles.push_back(pair<int,int>((1+j),(-i)));
		    }
		  aoe_tiles.push_back(pair<int,int>((1+i),(-i)));
		}
	      
	    }
	  else if( the_spell->GetSpellStats()->GetDirection()==S_DOWN )
	    {
	      for(int i=0;i<radius;i++)
		{ 
		  aoe_tiles.push_back(pair<int,int>((-1-i),(i)));
		  for(int j=-i-1;j<i;j++)
		    {
		      aoe_tiles.push_back(pair<int,int>((-1-j),(i)));
		    }
		  aoe_tiles.push_back(pair<int,int>((1+i),(i)));	
		}
	    }
	  else if(the_spell->GetSpellStats()->GetDirection()==S_LEFT )
	    {
	      for(int i=0;i<radius;i++)
		{ 
		  aoe_tiles.push_back(pair<int,int>((-i),(i+1)));
		  for(int j=-i-1;j<i;j++)
		    {
		      aoe_tiles.push_back(pair<int,int>((-i),(-1-j)));
		    }
		  aoe_tiles.push_back(pair<int,int>((-i),(-i-1)));
		  }
	    }
	  else if(the_spell->GetSpellStats()->GetDirection()==S_RIGHT )
	    {
	      for(int i=0;i<radius;i++)
		{ 
		  aoe_tiles.push_back(pair<int,int>((i),(i+1)));
		  for(int j=-i-1;j<i;j++)
		    {
		      aoe_tiles.push_back(pair<int,int>((i),(1+j)));
		    }
		  aoe_tiles.push_back(pair<int,int>((i),(-i-1)));
		  }
	    }
	  break;
	}
      
    }
}

void SpellState::Execute(pair<int,int> pos)
{
  int tile_size=MapIndex::Instance()->getMap()->getTileSize();
  pos.first=pos.first/tile_size*tile_size;
  pos.second=pos.second/tile_size*tile_size;//x,y are the top-left coordinates thus we need to place it tile_size below
  if(!the_turn->StandardActionDone())
    {
      Caster *caster=dynamic_cast<Caster*>(the_turn->TheCharacter());
  
      if(caster->CastSpell(spell,pos))
	{
	  the_turn->SetStandardAction(true);
	}
      else
	{
	  cout<<"NOPE NO SPELL FOR YOU!"<<endl;
	}
    }
  Done=true;
}


ItemState::ItemState(Turn *the_turn,string item):InputState(the_turn),item(item)
{
  BaseCharacter *bchar=the_turn->TheCharacter();
  int radius=1;
  int tile_size=MapIndex::Instance()->getMap()->getTileSize();
  tiles=MapIndex::Instance()->getTilesInRange(bchar->getPosition().x/tile_size,bchar->getPosition().y/tile_size,radius,true);
  aoe_tiles.push_back(pair<int,int>(0,0));
}

void ItemState::Execute(pair<int,int> pos)
{
  
  if(!the_turn->StandardActionDone())
    {
      UsableItem* usableitem=dynamic_cast<UsableItem*>(the_turn->TheCharacter()->getInventoryItem(item));
      if(usableitem)
	{
	  cout<<"Item:"<<usableitem->getInfo()->getName()<<endl;
	  usableitem->Use(pos);
	  the_turn->SetStandardAction(true);
	}
      else
	{
	  cout<<"No Such Usable Item"<<endl;
	}
    }
  Done=true;
}
