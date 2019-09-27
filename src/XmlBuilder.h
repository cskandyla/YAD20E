#include "AnimatedEntity.h"
#include "Stats.h"
#include "Info.h"
#include "BasicCharacter.h"
#include "Mage.h"
#include "Warrior.h"
#include "Item.h"
#include "VisibleItem.h"
#include "Weapon.h"
#include "UsableItem.h"
#include "Spell.h"
#include "TargetSpell.h"
#include "SpellBlast.h"
#include "EOTSpell.h"
#include "CloudSpell.h"
#include "WallSpell.h"
#include "LineSpell.h"
#include "ConeSpell.h"
#include "SpellEffects.h"
#include "Effect.h"
#include "Team.h"
#include "Doodad.h"
#include "DoodadFunctions.h"
#include <pugixml.hpp>
#include "Quest.h"
#include <lua.hpp>
using namespace pugi;
using std::string;

#ifndef __MXMLBUILDER__
#define __MXMLBUILDER__

//Load Stuff from xml
class XmlBuilder
{
private:
	XmlBuilder();
	//SpellEffects table
	//
public:
    
	static SDL_Renderer *renderer;
	//Init
	static void ParseInit(string InitFile,string &map,string &mapsetting);
	static void ParseMapSetting(string mapsetting,int &visibility);

    
	//Class Factory
	static AnimatedEntity*   LoadEntity(string xmlfile,string entity_name);//DONE
	static Attributes*       LoadAttributes(string xmlfile);
	static GeneralStats*     LoadGeneralStats(string xmlfile);
	static Stats*            LoadStats(string xmlfile);//DONE
	static Info*             LoadInfo(string xmlfile);//DONE
	static Projectile*       LoadProjectile(string xmlfile);
	static ItemInfo*         LoadItemInfo(string xmlfile);
	static Item*             LoadItem(string xmlfile);
	static BaseCharacter*    LoadCharacter(string xmlfile);//-->to implementation
	static SpellInfo*        LoadSpellInfo(string xmlfile);
	static SpellStats*       LoadSpellStats(string xmlfile,string stats_name);
	static Spell*            LoadSpell(string xmlfile);
	static void              LoadSpells(string xmlfile,Mage *the_mage);
	static Effect*           LoadEffect(string xmlfile);//implement if needed should be straightforward
	static void              LoadTeams(string xmlfile);
	static Doodad*           LoadDoodad(string xmlfile);
	static void              LoadDoodads(string xmlfile);
	static Quest*            LoadQuest(string xmlfile, lua_State *l);

};
#endif
