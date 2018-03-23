#include "Primitives.h"
#include <cmath>
void Primitives::DrawPixel(SDL_Surface *screen, int x, int y, Uint8 r, Uint8 g, Uint8 b)
{
  Uint32 *pixmem32;
  Uint32 colour;  
 
  colour = SDL_MapRGB( screen->format, r, g, b );
  
  pixmem32 = (Uint32*) screen->pixels  + y + x;
  *pixmem32 = colour;
}

void Primitives::DrawLine(SDL_Surface *screen, int x0, int y0, int x1, int y1, Uint8 r, Uint8 g, Uint8 b)
{	 
  int i;
  double x = x1 - x0;
  double y = y1 - y0;
  double length = sqrt( x*x + y*y );
  double addx = x / length;
  double addy = y / length;
  x = x0;
  y = y0;
  for ( i = 0; i < length; i += 1) {
    DrawPixel(screen,x,y,r,g,b);
    x += addx;
    y += addy;
  }

}
