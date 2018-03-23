#include <SDL2/SDL.h>
#include <utility>
#include <vector>
using std::vector;
using std::pair;

#ifndef __GRIDCELLS__H
#define __GRIDCELLS__H

class GridCells
{
 private:
  vector< pair < SDL_Rect,SDL_Surface*> >grid_cells;
 public:
  GridCells(int xpos,int ypos,int radius,int alpha);
  void Draw(SDL_Surface *screen);
  ~GridCells();
};

#endif
