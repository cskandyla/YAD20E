#include "InfoSurface.h"
#include "map.h"
#include "MapIndex.h"
#include <lua.hpp>
//#include "BasicCharacter.h"
#ifndef __GAME__
#define __GAME__
//actually never to be used
//just for a convienient thing to pass to lua for debugging
struct Game
{
  InfoSurface* Log;
  Map *map;
  MapIndex *mindex;
  lua_State *lua_state;
};
#endif // __GAME
