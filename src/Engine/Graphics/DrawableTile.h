#include <SDL2/SDL.h>

#ifndef __DRAWBLETILE__H
#define __DRAWBLETILE__H

class DrawableTile
{
 private:
  SDL_Rect pos;
  SDL_Texture *texture;
 public:
  DrawableTile(int x,int y,int size,SDL_Color c,unsigned char alpha);
  virtual ~DrawableTile();
  void Draw(int x,int y,SDL_Texture *screen);
};

#endif
