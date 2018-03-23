#include <string>
#include <SDL2/SDL.h>
using namespace std;

#ifndef MISCELLANEOUS__H
#define MISCELLANEOUS__H

SDL_Surface* loadSurface( std::string path );
SDL_Texture* loadTexture(std::string image,SDL_Renderer *renderer);
SDL_Cursor *create_xpm_cursor(const char *image[]);
void CreateDirectory(string dir);

#endif //  MISCELLANEOUS__H
