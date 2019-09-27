#include <lua.hpp>
#include <string>
using std::string;

//Simplest Possible implementation cattering for 'non-engine' programmers some
//metatable magic in the Character and item to simulate OO Behaviour generally
//should be used to quickly change behaviour rather than actually code complex
//constructs => setAI's and fill inventories vs Implementing AI States
//That said, probable interface for:
//triggers-- rectangular shape 
//victory conditions--check on EOT

//LUA STRUCTURES
#define LUA_LOG       "Log"
#define LUA_CONSOLE   "Console"
#define LUA_MAP       "Map"
#define LUA_CHARACTER "Character"
#define LUA_ITEM      "Item"
#define LUA_DOODAD    "Doodad"


class Lua_Export_Manager
{

};

//Register EVERYTHING
void lua_register_everything(lua_State *l);
void lua_list_commands();
//GLOBALS
int ListCharacters(lua_State *l);
int ListItems(lua_State *l);
int ListDoodads(lua_State *l);
int LoadItem(lua_State *l);
int LoadCharacter(lua_State *l);
int LoadDoodad(lua_State *l);
int LoadMap(lua_State *l);
int SwitchMap(lua_State *l);
int SetVisualMode(lua_State *l);
void lua_register_globals(lua_State *l);

int switch_map(lua_State *l);

//Console
//we've got a global console so we probably want globals
int console_print(lua_State *l);
int console_clear(lua_State *l);

//Log
//we probably want a global log named LOG
int log_print(lua_State *l);
int log_clear(lua_State *l);

//Character
int character_get(lua_State *l);//by ID
int character_unlink(lua_State *l);
int character_place(lua_State *l);//in tiles
int character_equip(lua_State *l);//Actual Item object
int character_addinventory(lua_State *l);// Actual Item object
int character_move(lua_State *l);// absolute position
int character_info(lua_State *l);
int character_set_ai(lua_State *l);
int character_get_state(lua_State *l);
int character_get_id(lua_State *l);
int character_get_name(lua_State *l);
void lua_register_character(lua_State *l);

//Item

int item_get(lua_State *l);//by ID
int item_place(lua_State *l);// in tiles
int item_info(lua_State *l);
int item_trigger(lua_State *l);// what happens when you click it i.e. quest end
void lua_register_item(lua_State *l);


//Doodad
int doodad_get(lua_State *l);//by ID
int doodad_place(lua_State *l);// in tiles
int doodad_trigger(lua_State *l);
int doodad_info(lua_State *l);
int doodad_get_state(lua_State *l);
void lua_register_doodad(lua_State *l);



//Objectives
bool lua_objective_function(lua_State *l,string name);
