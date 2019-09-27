#include "BaseRenderer.h"
#include <iostream>
using std::cout;
using std::endl;

//SINGLETON force 1 renderer and enable reuse everywhere
BaseRenderer* BaseRenderer::b_renderer=NULL;

BaseRenderer::BaseRenderer()
{

}

bool BaseRenderer::Init(SDL_Renderer *renderer)
{
	if(renderer)
	{
		this->renderer=renderer;
		return true;
	}
	return false;
}
void BaseRenderer::Free()
{
  SDL_DestroyRenderer(renderer);
}
BaseRenderer* BaseRenderer::Instance()
{
  if(!b_renderer)
    b_renderer=new BaseRenderer();
      return b_renderer;
}
SDL_Renderer* BaseRenderer::Renderer()
{
  return renderer;
}
SDL_Texture* BaseRenderer::LoadImage(string textureimage)
{
  SDL_Texture* newTexture = NULL;
  SDL_Surface* loadedSurface = IMG_Load( textureimage.c_str() );
 if( loadedSurface == NULL )
   {
     printf( "Unable to load image %s! SDL_image Error: %s\n", textureimage.c_str(),IMG_GetError() );
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
	 printf( "Unable to create texture from %s! SDL Error: %s\n", textureimage.c_str(), SDL_GetError() );
       } //Get rid of old loaded surface
     SDL_FreeSurface( loadedSurface );
   }
 return newTexture;
}
void BaseRenderer::RenderTexture(SDL_Texture *srctexture,SDL_Texture *tgttexture,SDL_Rect *srcrect,SDL_Rect *tgtrect)
{
  //SDL_RenderClear(renderer);
	SDL_SetRenderTarget(renderer,tgttexture);
	SDL_RenderCopy(renderer,srctexture,srcrect,tgtrect);
	SDL_SetRenderTarget(renderer,NULL);
}


void BaseRenderer::Render(SDL_Texture *tex,SDL_Rect *tgtrect)
{
  SDL_RenderCopy(renderer,tex,NULL,tgtrect);
}
void BaseRenderer::RenderPart(SDL_Texture *tex,SDL_Rect *srcrect,SDL_Rect *tgtrect)
{
  SDL_RenderCopy(renderer,tex,srcrect,tgtrect);
}
