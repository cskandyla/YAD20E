#include "Lua_Export.h"
#include "MapIndex.h"
#include "XmlBuilder.h"
#include "BasicCharacter.h"
#include "KnowledgePool.h"
#include "Item.h"
#include <iostream>
using std::cout;
using std::endl;
// Just list all characters no arguements
int ListCharacters(lua_State *l)
{
  if(KnowledgePool::Instance()->getCharacters().size()==0)
    {
      cout<<"No Characters Registered Yet"<<endl;
    }
  unordered_map<unsigned int,BaseCharacter*>::iterator it;
  for(it=KnowledgePool::Instance()->getCharacters().begin();it!=KnowledgePool::Instance()->getCharacters().end();++it)
    {
      cout<<(*it).first<<" "<<(*it).second->getInfo()->getName()<<endl;
    }
  return 0;
}
// Just list all items no arguements
int ListItems(lua_State *l)
{
  unordered_map<unsigned int,Item*>::iterator it;
  if(KnowledgePool::Instance()->getItems().size()==0)
    {
      cout<<"No Items Registered Yet"<<endl;
    }
  for(it=KnowledgePool::Instance()->getItems().begin();it!=KnowledgePool::Instance()->getItems().end();++it)
    {
      cout<<(*it).first<<" "<<(*it).second->getInfo()->getName()<<endl;
    }
  return 0;
}

int ListDoodads(lua_State *l)
{
unordered_map<unsigned int,Doodad*>::iterator it;
  if(MapIndex::Instance()->getDoodads().size()==0)
    {
      cout<<"No Items Registered Yet"<<endl;
    }
  int tile_size=MapIndex::Instance()->getMap()->getTileSize();
  for(it=MapIndex::Instance()->getDoodads().begin();it!=MapIndex::Instance()->getDoodads().end();++it)
    {
      cout<<(*it).first<<"at:"<<(*it).second->GetEntity()->getPosition().x/tile_size<<','<<(*it).second->GetEntity()->getPosition().y/tile_size<<endl;
    }
  return 0;
}
//Insert a new character into the engine from an xml file
int LoadCharacter(lua_State *l)
{
  //get the string from the top of lua
  string xmlfile = luaL_checkstring(l, 1);
  BaseCharacter *character=XmlBuilder::LoadCharacter(xmlfile);
  if(character)
  KnowledgePool::Instance()->AddCharacter(character);
  return 0;
}
//Insert a new item into the engine from an xml file
int LoadItem(lua_State *l)
{
  string xmlfile = luaL_checkstring(l, 1);
  Item *item=XmlBuilder::LoadItem(xmlfile);

  if(item)
  KnowledgePool::Instance()->AddItem(item);
  return 0;
}
int LoadDoodad(lua_State *l)
{
  string xmlfile = luaL_checkstring(l, 1);
  Doodad *doodad=XmlBuilder::LoadDoodad(xmlfile);
  if(doodad)
  MapIndex::Instance()->AddDoodad(doodad);
  return 0;
}
//Load a new map from an xml file store the map object somewhere probably in the infobase;
int LoadMap(lua_State *l)
{
  
}
//Switch Map
int SwitchMap(lua_State *l)
{

}

int SetVisualMode(lua_State *l)
{
  string mode=luaL_checkstring(l,1);
  if(mode.compare("ALL")==0)
    {
      MapIndex::Instance()->getMap()->SetVisibleLayer(SALL);      
    }

  else if(mode.compare("VISIBLE")==0)
    {
      MapIndex::Instance()->getMap()->SetVisibleLayer(SVISIBLE);
    }
  else if(mode.compare("COLISION")==0)
    {
      MapIndex::Instance()->getMap()->SetVisibleLayer(SCOLISION);
    }
  return 0;
}

void lua_register_globals(lua_State *l)
{
  lua_pushcfunction(l, ListCharacters);
  lua_setglobal(l, "listcharacters");
  lua_pushcfunction(l, ListItems);
  lua_setglobal(l, "listitems");
  lua_pushcfunction(l, ListDoodads);
  lua_setglobal(l, "listdoodads");
  lua_pushcfunction(l, LoadCharacter);
  lua_setglobal(l, "LoadCharacter");
  lua_pushcfunction(l, LoadItem);
  lua_setglobal(l, "LoadItem");
  lua_pushcfunction(l, LoadDoodad);
  lua_setglobal(l, "LoadDoodad");
  lua_pushcfunction(l, SetVisualMode);
  lua_setglobal(l, "VisualMode");
}



//CHARACTER
int character_get(lua_State *l)
{
  //Load an int from lua
  int id= luaL_checknumber(l, 1);
  BaseCharacter *chara=KnowledgePool::Instance()->getCharacter(id);
  //Push a Character** to lua
 
  //  cout<<"Probably got a character"<<chara->getInfo()->getName()<<endl;
  BaseCharacter ** pchar = (BaseCharacter **)lua_newuserdata(l, sizeof(BaseCharacter *));
  *pchar=chara;
  luaL_setmetatable(l, LUA_CHARACTER);
  return 1;
}
int character_unlink(lua_State *l)
{

}
//coordinates in tiles
int character_place(lua_State *l)
{
  BaseCharacter *chara=*(BaseCharacter**)luaL_checkudata(l, 1, LUA_CHARACTER);

  int xpos=luaL_checknumber(l,2);
  int ypos=luaL_checknumber(l,3);
  // cout<<"Placing  character:"<<chara->getInfo()->getName()<<"at:"<<xpos<<','<<ypos<<endl;
  int tile_size=MapIndex::Instance()->getMap()->getTileSize();
  if(xpos<MapIndex::Instance()->getMap()->getWidth() && ypos<MapIndex::Instance()->getMap()->getHeight() && xpos>=0  && ypos>=0)
    {
      if(MapIndex::Instance()->IsPathable(xpos,ypos))
	{
	  chara->SetPosition(xpos*tile_size,ypos*tile_size);
	  MapIndex::Instance()->CharIndexUpdate(chara,0,0);
	}
      else
	{
	  cout<<"can not place a character there the space is already occupied by:"<<MapIndex::Instance()->getTileContent(xpos,ypos)<<" or is a wall"<<endl;
	}
    }
  
  return 0;
}
// absolute position
int character_move(lua_State *l)
{

  BaseCharacter *chara=*(BaseCharacter**)luaL_checkudata(l, 1, LUA_CHARACTER);
  int xpos=luaL_checknumber(l,2);
  int ypos=luaL_checknumber(l,3);
  if(xpos<MapIndex::Instance()->getMap()->getWidth()*MapIndex::Instance()->getMap()->getTileSize()
     && ypos<MapIndex::Instance()->getMap()->getHeight()*MapIndex::Instance()->getMap()->getTileSize()
     && xpos>=0  && ypos>=0)
  chara->SetPosition(xpos,ypos);
  return 0;

}

int character_equip(lua_State *l)
{
  cout<<"Equip Called"<<endl;
  BaseCharacter *chara=*(BaseCharacter**)luaL_checkudata(l, 1, LUA_CHARACTER);
  cout<<"Probably got a character"<<chara->getInfo()->getName()<<endl;
  Item *it=*(Item**)luaL_checkudata(l, 2, LUA_ITEM);
  cout<<"Loading item"<<it->getInfo()->getName()<<endl;
  chara->Equip(it);
  KnowledgePool::Instance()->RemoveItem(it->getID());
  //Reset Placement 
  chara->SetPosition(chara->getPosition().x,chara->getPosition().y);
  return 0;
}
int character_addinventory(lua_State *l)
{
  BaseCharacter *chara=*(BaseCharacter**)luaL_checkudata(l, 1, LUA_CHARACTER);
  Item *it=*(Item**)luaL_checkudata(l, 2, LUA_ITEM);
  cout<<"Adding "<<it->getInfo()->getName()<<" to "<<chara->getInfo()->getName()<<"'s inventory"<<endl;
  chara->AddItemToInventory(it);
  cout<<"Trying to remove item with ID:"<<it->getID()<<endl;
  KnowledgePool::Instance()->RemoveItem(it->getID());
  return 0;
  
}
//for now character,AI,target
int character_set_ai(lua_State *l)
{
BaseCharacter *chara=*(BaseCharacter**)luaL_checkudata(l, 1, LUA_CHARACTER);
string ai=luaL_checkstring(l,2);
BaseCharacter *target=*(BaseCharacter**)luaL_checkudata(l, 3, LUA_CHARACTER);
KnowledgePool::Instance()->AddAIEntity(chara->getID(),new Zombie(chara));
 
 
  
}

void lua_register_character(lua_State *l)
{
  lua_register(l,LUA_CHARACTER , character_get);
  luaL_newmetatable(l, LUA_CHARACTER);
  lua_pushcfunction(l, character_unlink); lua_setfield(l, -2, "__gc");
  lua_pushvalue(l, -1); lua_setfield(l, -2, "__index");
  lua_pushcfunction(l, character_place); lua_setfield(l, -2, "Place");
  lua_pushcfunction(l, character_move); lua_setfield(l, -2, "Move");
  lua_pushcfunction(l, character_equip); lua_setfield(l, -2, "Equip");
  lua_pushcfunction(l, character_addinventory); lua_setfield(l, -2, "Store");
  lua_pop(l, 1);
  
}


//ITEM
int item_get(lua_State *l)
{
  //Load an int from lua
  int id= luaL_checknumber(l, 1);
  Item *item=KnowledgePool::Instance()->getItem(id);
  if(item!=NULL)
    {
      Item **pitem = (Item **)lua_newuserdata(l, sizeof(Item *));
      cout<<"Loading item"<<item->getInfo()->getName()<<endl;;
      *pitem=item;
      luaL_setmetatable(l, LUA_ITEM);
      return 1;
    }
  else
    {
      return 0;
    }
}

int item_unlink(lua_State *l)
{

}

int item_tests(lua_State *l)
{

  Item *item=*(Item**)luaL_checkudata(l, 1, LUA_ITEM);
  cout<<"Testing"<<item->getInfo()->getName()<<endl;
  if(dynamic_cast<Weapon*>(item)!=NULL)
    {
      cout<<"We Got a weapon"<<endl;
    }

  return 0;
}

int item_place(lua_State *l)
{
  Item *item=*(Item**)luaL_checkudata(l, 1, LUA_ITEM);

  int xpos=luaL_checknumber(l,2);
  int ypos=luaL_checknumber(l,3);
  // cout<<"Placing  character:"<<chara->getInfo()->getName()<<"at:"<<xpos<<','<<ypos<<endl;
  int tile_size=MapIndex::Instance()->getMap()->getTileSize();
  if(xpos<MapIndex::Instance()->getMap()->getWidth() && ypos<MapIndex::Instance()->getMap()->getHeight() && xpos>=0  && ypos>=0)
    {

      if(MapIndex::Instance()->IsPathable(xpos,ypos))
	{
	  item->SetPosition(xpos*tile_size,ypos*tile_size);
	  MapIndex::Instance()->ItemIndexUpdate(item,0,0);
	}
      else
	{
	  cout<<"can not place a character there the space is already occupied by:"<<MapIndex::Instance()->getTileContent(xpos,ypos)<<" or is a wall"<<endl;
	}
      

    }
  return 0;

}

void lua_register_item(lua_State *l)
{

  lua_register(l,LUA_ITEM , item_get);
  luaL_newmetatable(l, LUA_ITEM);
  lua_pushcfunction(l, item_unlink); lua_setfield(l, -2, "__gc");
  lua_pushvalue(l, -1); lua_setfield(l, -2, "__index");
  lua_pushcfunction(l, item_place); lua_setfield(l, -2, "Place");
  lua_pushcfunction(l, item_tests); lua_setfield(l, -2, "Test");
  lua_pop(l, 1);

}



//DOODAD
int doodad_get(lua_State *l)
{
  //Load an int from lua
  int id= luaL_checknumber(l, 1);
  Doodad *doodad=MapIndex::Instance()->getDoodad(id);
  if(doodad!=NULL)
    {
      Doodad **pdoodad = (Doodad **)lua_newuserdata(l, sizeof(Item *));
      cout<<"Loading Doodad "<<doodad->GetID()<<endl;;
      *pdoodad=doodad;
      luaL_setmetatable(l, LUA_DOODAD);
      return 1;
    }
  else
    {
      return 0;
    }
}

int doodad_unlink(lua_State *l)
{

}



int doodad_place(lua_State *l)
{
  Doodad *doodad=*(Doodad**)luaL_checkudata(l, 1, LUA_DOODAD);

  int xpos=luaL_checknumber(l,2);
  int ypos=luaL_checknumber(l,3);
  // cout<<"Placing  character:"<<chara->getInfo()->getName()<<"at:"<<xpos<<','<<ypos<<endl;
  int tile_size=MapIndex::Instance()->getMap()->getTileSize();
  if(xpos<MapIndex::Instance()->getMap()->getWidth() && ypos<MapIndex::Instance()->getMap()->getHeight() && xpos>=0  && ypos>=0)
    {
      doodad->GetEntity()->setPosition(xpos*tile_size,ypos*tile_size);
      MapIndex::Instance()->DoodadIndexUpdate(doodad,0,0);
    }
  return 0;

}

int doodad_trigger(lua_State *l)
{
  Doodad *doodad=*(Doodad**)luaL_checkudata(l, 1, LUA_DOODAD);
  int tile_size=MapIndex::Instance()->getMap()->getTileSize();
  doodad->Trigger();
  return 0;

}

void lua_register_doodad(lua_State *l)
{

  lua_register(l,LUA_DOODAD , doodad_get);
  luaL_newmetatable(l, LUA_DOODAD);
  lua_pushcfunction(l, doodad_unlink); lua_setfield(l, -2, "__gc");
  lua_pushvalue(l, -1); lua_setfield(l, -2, "__index");
  lua_pushcfunction(l, doodad_place); lua_setfield(l, -2, "Place");
  lua_pushcfunction(l, doodad_trigger); lua_setfield(l, -2, "Trigger");
  lua_pop(l, 1);

}





void lua_register_everything(lua_State *l)
{
  lua_register_globals(l);
  lua_register_character(l);
  lua_register_item(l);
  lua_register_doodad(l);

}
