#include "Realm.h"




Realm::Realm(Map *the_map,BaseCharacter *the_character, Quest *the_quest)
{
	this->the_map=the_map;
	this->the_character=the_character;
	this->the_quest=the_quest;
}
Realm::~Realm()
{
}
Quest* Realm::getQuest()
{
	return this->the_quest;
}
Map* Realm::getMap()
{
	return this->the_map;
}
BaseCharacter* Realm::getCharacter()
{
	return this->the_character;
}

