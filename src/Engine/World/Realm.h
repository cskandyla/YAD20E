#include "map.h"
#include "BasicCharacter.h"
#include "Quest.h"

#ifndef REALM_H
#define REALM_H



/* 
 * The real class holds the relevant infromation required to instantiate a battle.
 * The character pointer to the hero is optional used to overide the default playable hero
 * if required. 
*/


class Realm
{
private:
	Map *the_map;
	Quest *the_quest;
	BaseCharacter *the_character;

public:
	Realm(Map *the_map,BaseCharacter *the_character, Quest *the_quest);
	~Realm();
	Quest *getQuest();
	Map   *getMap();
	BaseCharacter *getCharacter();
	
};

#endif
