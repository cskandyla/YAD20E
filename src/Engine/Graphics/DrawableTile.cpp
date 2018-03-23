#include "DrawableTile.h"
#include "Primitives.h"
#include "params.h"
#include "BaseRenderer.h"
DrawableTile::DrawableTile(int x,int y,int size,SDL_Color c,unsigned char alpha)
 {
   pos.x=x;
   pos.y=y;
   pos.w=size;
   pos.h=size;
   texture=SDL_CreateTexture(BaseRenderer::Instance()->Renderer(), SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, size,size);
   SDL_SetRenderTarget(BaseRenderer::Instance()->Renderer(),texture);
   SDL_SetTextureBlendMode(texture, SDL_BLENDMODE_BLEND);
   SDL_SetRenderDrawColor(BaseRenderer::Instance()->Renderer(),c.r,c.g,c.b,255);
   SDL_SetTextureAlphaMod( texture, alpha );
   SDL_RenderClear(BaseRenderer::Instance()->Renderer());
   SDL_RenderFillRect(BaseRenderer::Instance()->Renderer() , &pos);
   SDL_SetRenderTarget(BaseRenderer::Instance()->Renderer(),NULL);
   
   
     
 }

DrawableTile::~DrawableTile()
{
  SDL_DestroyTexture(texture);
}

void DrawableTile::Draw(int x,int y,SDL_Texture *screen)
{
  pos.x=x/pos.w*pos.w;
  pos.y=y/pos.w*pos.w;
  
  // SDL_BlitSurface(tile_surf,NULL,screen,&pos);
  //  SDL_RenderCopy(renderer,texture,NULL,&pos);
  BaseRenderer::Instance()->RenderTexture(texture,screen,NULL,&pos);
}

