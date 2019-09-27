#include "miscellaneous.h"
#define TILE_SIZE 30
#include <SDL2/SDL_image.h>
#ifdef __linux__
#elif __WIN32
#include <direct.h>
#endif

SDL_Surface* loadSurface( std::string path )
{
    SDL_Surface* orig_surf = IMG_Load( path.c_str());
    if( orig_surf == NULL )
    {
        printf( "Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError() );
    }
    //Load image at specified path
    SDL_Surface* loadedSurface = SDL_ConvertSurface(orig_surf,orig_surf->format,0);
    SDL_FreeSurface(orig_surf);
    if( loadedSurface == NULL )
    {
        printf( "Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError() );
    }


    Uint32 *pixels = (Uint32 *)loadedSurface->pixels;
    Uint8 r,g,b,a;
    SDL_GetRGB(pixels[0],loadedSurface->format,&r,&g,&b);
    SDL_SetColorKey(loadedSurface, SDL_TRUE,SDL_MapRGB( loadedSurface->format, 0, 0, 0) );

    return loadedSurface;
}

SDL_Texture* loadTexture(std::string image,SDL_Renderer *renderer)
{
  SDL_Texture* newTexture = NULL;
  SDL_Surface* loadedSurface = IMG_Load( image.c_str() );
 if( loadedSurface == NULL )
   { printf( "Unable to load image %s! SDL_image Error: %s\n", image.c_str(),
	     IMG_GetError() );
   }
 else
   { //Create texture from surface pixels
     Uint32 *pixels = (Uint32 *)loadedSurface->pixels;
     Uint8 r,g,b,a;
     SDL_GetRGB(pixels[0],loadedSurface->format,&r,&g,&b);
     SDL_SetColorKey(loadedSurface, SDL_TRUE,SDL_MapRGB( loadedSurface->format, r, g, b) );
     newTexture = SDL_CreateTextureFromSurface( renderer, loadedSurface );
     if( newTexture == NULL )
       {
	 printf( "Unable to create texture from %s! SDL Error: %s\n", image.c_str(), SDL_GetError() );
       } //Get rid of old loaded surface
     SDL_FreeSurface( loadedSurface );
   }
 return newTexture;
}


void CreateDirectory(string dir)
{
#ifdef __linux__
#elif __WIN32
mkdir(dir.c_str());
#endif

}


SDL_Rect  Translate(SDL_Rect rect)
{
    SDL_Rect translated_rect;
    translated_rect.x=rect.x-(rect.w-TILE_SIZE)/2;
    translated_rect.y=rect.y-(rect.h-TILE_SIZE-TILE_SIZE/4);
    return translated_rect;
}



SDL_Cursor *create_xpm_cursor(const char *image[])
{
  int i, row, col;
  Uint8 data[4*32];
  Uint8 mask[4*32];
  int hot_x, hot_y;

  i = -1;
  for (row=0; row<32; ++row) {
    for (col=0; col<32; ++col) {
      if (col % 8) {
        data[i] <<= 1;
        mask[i] <<= 1;
      } else {
        ++i;
        data[i] = mask[i] = 0;
      }
      switch (image[4+row][col]) {
        case 'X':
          data[i] |= 0x01;
          mask[i] |= 0x01;
          break;
        case '.':
          mask[i] |= 0x01;
          break;
        case ' ':
          break;
      }
    }
  }
  sscanf(image[4+row], "%d,%d", &hot_x, &hot_y);
  return SDL_CreateCursor(data, mask, 32, 32, hot_x, hot_y);
}
