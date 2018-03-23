#include <SDL2/SDL.h>
#include <string>
#include <unordered_map>
using std::string;
using std::unordered_map;

#ifndef __M_CURSOR_H_
#define __M_CURSOR_H_

enum CURSOR_MODE{CURSOR_WALK=0,CURSOR_ATTACK,CURSOR_CAST,CURSOR_TALK,CURSOR_USE,CURSOR_LOOT};
		 //Singleton ?
class Cursor
{
 private:
  SDL_Surface *cursor_surf;
  unordered_map<CURSOR_MODE,SDL_Surface*> cursors;
 public:
  Cursor(CURSOR_MODE cm,SDL_Surface *cursor_surf);
  void Add(CURSOR_MODE cm,SDL_Surface *cursor_surf);
  bool SetMode(CURSOR_MODE cm);
  void Draw(int x,int y,SDL_Surface *screen);
};

#endif
