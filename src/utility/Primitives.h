#include <SDL2/SDL.h>

class Primitives
{
 public:
  static void DrawPixel(SDL_Surface *screen, int x, int y, Uint8 r, Uint8 g, Uint8 b);
  static void DrawLine(SDL_Surface *Screen, int x0, int y0, int x1, int y1, Uint8 r, Uint8 g, Uint8 b);

};
