#include <SDL2/SDL.h>
#include <unordered_map>
#include <string>
using std::unordered_map;
using std::string;
#include "MapIndex.h"
#include "map.h"
#include "AIEntity.h"
#include "TurnEngine.h"
#include "BasicCharacter.h"
#include "XmlBuilder.h"
#include "AIDefines.h"
#include "Renderer.h"
#include "miscellaneous.h"
#include "XmlBuilder.h"
#include "params.h"
#include "SpellBlast.h"
#include "TargetSpell.h"
#include <pugixml.hpp>
#include <lua.hpp>
using namespace pugi;


#ifndef  __GAME_ENGINE__
#define  __GAME_ENGINE__
class Camera;
class GameEngine
{
private:
	Camera *camera;
	SDL_Texture *Game_Texture;
	SDL_Rect *Game_Surface_Rect;
	TurnEngine *TE;
	Map *the_map;
	BaseCharacter* the_char;
	GameRenderer *g_renderer;
	lua_State *l;
//  unordered_map<unsigned int,AIEntity*> AI;//AIHandler Class?

 public:
  GameEngine(lua_State *l);
  virtual ~GameEngine();
  void DummyInit(/*STUFF HERE*/);
  bool Init(string XMLFile, SDL_Rect *GameScreenSurface);
  void Update(float time);
  void Handle_Events(SDL_Event *event);
  void Draw(SDL_Texture *maintexture);
  Camera* getCamera();
  SDL_Texture* getGameTex(){return Game_Texture;}
  SDL_Rect*    getViewpoint();
  TurnEngine* getTurnEngine();
  BaseCharacter* getTheChar(){return the_char;}
  
};


#endif
