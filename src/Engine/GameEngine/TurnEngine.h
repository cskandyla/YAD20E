#include "Turn.h"
#include <SDL2/SDL.h>
#include <deque>
#include <set>
#include "InfoSurface.h"
#include "AIEntity.h"
#include "Quest.h"

#ifndef __TURN_ENGINE__
#define  __TURN_ENGINE__

class Camera;
class TurnEngine
{

private:
	Turn *the_turn;
	Camera *camera;
	//Holds known chars used to check if a character has been added
	int known_chars;
	std::deque<unsigned int> turn_order;
	std::unordered_map<unsigned int,BaseCharacter*>::iterator it;
	InfoSurface *Log;
	Quest *the_quest;
	bool quest_done;

public:
	TurnEngine(Camera *camera,Quest *the_quest);
	virtual ~TurnEngine();
	void Update(float time);
	void Handle_Events(SDL_Event *event);
	Turn* NextTurn();
	Turn* GetTurn();
	Camera* GetCamera();
	void AddTurn(unsigned int character_id);
};

#endif
