#include "Lua_Export.h"
#include "MapIndex.h"
#include "XmlBuilder.h"
#include "BasicCharacter.h"
#include "KnowledgePool.h"
#include "Item.h"
#include "Zombie.h"
#include <iostream>
using std::cout;
using std::endl;
// Just list all characters no arguements


int lua_list_commands(lua_State *l)
{
	cout<<"Globals:"<<endl;
	cout<<"listcharacters"<<endl;
	cout<< "listitems" <<endl;
	cout<<"listdoodads"   <<endl;
	cout<<"LoadCharacter" <<endl;
	cout<<"LoadItem"      <<endl;
	cout<<"LoadDoodad"    <<endl;
	cout<<"VisualMode"    <<endl;
	cout<<"Log" <<endl;
	
	cout<<"Character:"<<endl;
	cout<< "\tPlace(x,y) in tiles" << endl;
	cout<<"\tMove(x,y) in coords"   << endl;
	cout<< "\tEquip(itemref)" << endl;
	cout<< "\tStore(itemref)" << endl;
	cout<< "\tSetAI(targetref)" << endl;

	cout<<"Item:"<<endl;	
	cout<<"\tPlace(x,y) in tiles" <<endl;
	cout<<"\tTest()"  <<endl;

	cout<<"Doodad"<<endl;
	cout<< "\tPlace(x,y) in tiles"    << endl;
	cout<< "\tTrigger()"   << endl;

	return 0;
}

int LogPrint(lua_State *l)
{
	string message = luaL_checkstring(l, 1);
	cout<<"HAXTEST"<<message<<endl;
	//Log->Print()
	return 0;
}

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
	{
		cout<<"Loaded"<<character->getInfo()->getName()<<endl;
		KnowledgePool::Instance()->AddCharacter(character);
		character->SetPosition(0,0);
		MapIndex::Instance()->AddCharacter(character);
		MapIndex::Instance()->CharIndexUpdate(character,0,0);
		
	}
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
	return 0;
}
//Switch Map
int SwitchMap(lua_State *l)
{
	return 0;
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
	lua_pushcfunction(l,LogPrint);
	lua_setglobal(l,"Log");
	lua_pushcfunction(l,lua_list_commands);
	lua_setglobal(l,"Help");
	
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
	return 0;
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
			cout<<"placing at:"<<xpos<<','<<ypos<<endl;
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
	//I do not have acccess to the pointer let's use the ID instead
	BaseCharacter *target=*(BaseCharacter**)luaL_checkudata(l, 3, LUA_CHARACTER);
	//BaseCharacter *target=KnowledgePool::Instance()->getCharacter(1);
	if(chara!=NULL && target !=NULL)
	{
		Zombie_AI *zombie=new Zombie_AI(chara);
		cout<<"Setting AI Target to:"<<target->getID();
		zombie->setTarget(target);
		KnowledgePool::Instance()->AddAIEntity(chara->getID(),zombie);
	}
 
	return 0;  
}


int character_get_state(lua_State *l)
{
	BaseCharacter *chara=*(BaseCharacter**)luaL_checkudata(l, 1, LUA_CHARACTER);
	lua_pushnumber(l,chara->getState());
	return 1;
}

int character_get_id(lua_State *l)
{
	BaseCharacter *chara=*(BaseCharacter**)luaL_checkudata(l, 1, LUA_CHARACTER);
	lua_pushnumber(l,chara->getID());
	return 1;
}


int character_get_name(lua_State *l)
{
	BaseCharacter *chara=*(BaseCharacter**)luaL_checkudata(l, 1, LUA_CHARACTER);
	lua_pushstring(l,chara->getInfo()->getName().c_str());
	return 1;	
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
	lua_pushcfunction(l, character_set_ai); lua_setfield(l, -2, "SetAI");
	lua_pushcfunction(l, character_get_state); lua_setfield(l, -2, "GetState");
	lua_pushcfunction(l, character_get_id); lua_setfield(l, -2, "GetID");
	lua_pushcfunction(l, character_get_name); lua_setfield(l, -2, "GetName");
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

	return 0;
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
	cout<<"Placing  item:"<<item->getInfo()->getName()<<"at:"<<xpos<<','<<ypos<<endl;
	int tile_size=MapIndex::Instance()->getMap()->getTileSize();
	if(xpos<MapIndex::Instance()->getMap()->getWidth() && ypos<MapIndex::Instance()->getMap()->getHeight() && xpos>=0  && ypos>=0)
	{

		if(MapIndex::Instance()->IsPathable(xpos,ypos))
		{
			//item->SetPosition(xpos*tile_size,ypos*tile_size);
			//MapIndex::Instance()->ItemIndexUpdate(item,0,0);
		}
		else
		{
			cout<<"can not place an item there the space is already occupied by:"<<MapIndex::Instance()->getTileContent(xpos,ypos)<<" or is a wall"<<endl;
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
	return 0;
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
		MapIndex::Instance()->DoodadIndexUpdate(doodad,0,0,doodad->getVisibility());
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

int doodad_get_state(lua_State *l)
{
	Doodad *doodad=*(Doodad**)luaL_checkudata(l, 1, LUA_DOODAD);
	lua_pushnumber(l,doodad->GetCurrentState());
	return 1;
}

void lua_register_doodad(lua_State *l)
{

	lua_register(l,LUA_DOODAD , doodad_get);
	luaL_newmetatable(l, LUA_DOODAD);
	lua_pushcfunction(l, doodad_unlink); lua_setfield(l, -2, "__gc");
	lua_pushvalue(l, -1); lua_setfield(l, -2, "__index");
	lua_pushcfunction(l, doodad_place); lua_setfield(l, -2, "Place");
	lua_pushcfunction(l, doodad_trigger); lua_setfield(l, -2, "Trigger");
	lua_pushcfunction(l, doodad_get_state); lua_setfield(l, -2, "GetState");
	lua_pop(l, 1);

}





void lua_register_everything(lua_State *l)
{
	lua_register_globals(l);
	lua_register_character(l);
	lua_register_item(l);
	lua_register_doodad(l);

}

