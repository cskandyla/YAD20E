#include "InfoSurface.h"
#include "miscellaneous.h"
#include "BaseRenderer.h"


InfoSurface::InfoSurface(char *backgroundimage,TTF_Font *font)
{
    this->font=font;
    this->background=loadTexture(backgroundimage,  BaseRenderer::Instance()->Renderer());
    this->startx=this->starty=this->posx=this->posy=0;
}

InfoSurface::InfoSurface(int width,int height,unsigned char r,unsigned char g,unsigned char b,int a,TTF_Font *font)
{
    this->font=font;
    this->background=SDL_CreateTexture( BaseRenderer::Instance()->Renderer(), SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, width,height);
    SDL_SetTextureBlendMode(background, SDL_BLENDMODE_BLEND);
    SDL_SetRenderDrawColor(BaseRenderer::Instance()->Renderer(),r,g,b,255);
    SDL_SetTextureAlphaMod( background, a );
    SDL_RenderClear(BaseRenderer::Instance()->Renderer());
    SDL_RenderFillRect(BaseRenderer::Instance()->Renderer() , NULL);
    SDL_SetRenderTarget(BaseRenderer::Instance()->Renderer(),NULL);
    this->startx=this->starty=this->posx=this->posy=0;
}

InfoSurface::~InfoSurface()
{

  deque<SDL_Texture*>::iterator  it;
  for(it=surfaces.begin();it!=surfaces.end();++it)
    {
      SDL_DestroyTexture(*it);
    }
  SDL_DestroyTexture(background);

}


void InfoSurface::AddText(char *text)
{
    this->text.push_back(string(text));    
    SDL_Surface *new_surf=TTF_RenderText_Solid(font,text,SDL_Color {0,0,0});
    this->surfaces.push_back(SDL_CreateTextureFromSurface(  BaseRenderer::Instance()->Renderer(), new_surf ));
    SDL_FreeSurface(new_surf);
}



void InfoSurface::AddText(char *text,unsigned char r,unsigned char g,unsigned char b)
{
    this->text.push_back(string(text));
    SDL_Color col = {r,g,b};
    SDL_Surface *new_surf=TTF_RenderText_Solid(font,text,col);
    this->surfaces.push_back(SDL_CreateTextureFromSurface(  BaseRenderer::Instance()->Renderer(), new_surf ));
    SDL_FreeSurface(new_surf);
}


void InfoSurface::AddText(string text)
{
    this->text.push_back(text);
    SDL_Surface *new_surf=TTF_RenderText_Solid(font,text.c_str(),SDL_Color {0,0,0});
    this->surfaces.push_back(SDL_CreateTextureFromSurface(  BaseRenderer::Instance()->Renderer(), new_surf ));
    SDL_FreeSurface(new_surf);
}


void InfoSurface::AddText(string text,unsigned char r,unsigned char g,unsigned char b)
{
    this->text.push_back(text);
    SDL_Surface *new_surf=TTF_RenderText_Solid(font,text.c_str(),SDL_Color {r,g,b});
    this->surfaces.push_back(SDL_CreateTextureFromSurface( BaseRenderer::Instance()->Renderer(), new_surf ));
    SDL_FreeSurface(new_surf);
}


void InfoSurface::Show(SDL_Texture *screen)
{
   SDL_SetRenderTarget(BaseRenderer::Instance()->Renderer(),background);
   SDL_SetRenderDrawColor(BaseRenderer::Instance()->Renderer(),0,0,0,255);
  SDL_RenderClear(BaseRenderer::Instance()->Renderer());
  SDL_Rect temp;
  //
  for(int i=0; i<surfaces.size(); i++)
    {
      temp.x=startx;//posx+startx;
      temp.y=posy+starty+i*TTF_FontHeight(font);
      SDL_QueryTexture(surfaces[i],NULL,NULL,&temp.w,&temp.h);
      //  SDL_RenderCopy(renderer,surfaces[i],NULL,&temp);
        BaseRenderer::Instance()->RenderTexture(surfaces[i],background,NULL,&temp);
	
    }
  
  temp.x=0;//posx;
  temp.y=posy;
  SDL_QueryTexture(background,NULL,NULL,&temp.w,&temp.h);
  BaseRenderer::Instance()->RenderTexture(background,screen,NULL,NULL);
}


void InfoSurface::Show(SDL_Texture *screen,int num)
{
  //SDL_RenderClear(renderer);
    SDL_Rect temp;
    temp.x=posx;
    temp.y=posy;
    //SDL_QueryTexture(background,NULL,NULL,&temp.w,&temp.h);
    //SDL_RenderCopy(renderer,background,NULL,&temp);
    BaseRenderer::Instance()->RenderTexture(background,screen,NULL,&temp);
    if(surfaces.size()<num)
        num=surfaces.size();

    for(int i=0; i<num; i++)
    {
        temp.x=posx+startx;
        temp.y=posy+starty+i*TTF_FontHeight(font);
	SDL_QueryTexture(surfaces[i],NULL,NULL,&temp.w,&temp.h);
	// SDL_RenderCopy(renderer,surfaces[i],NULL,&temp);
	  BaseRenderer::Instance()->RenderTexture(surfaces[i],screen,NULL,&temp);
    }
}



void InfoSurface::Show(SDL_Texture *screen,int start,int end)
{
  //SDL_RenderClear(renderer);
  SDL_Rect temp;
  temp.x=posx;
  temp.y=posy;
  //SDL_QueryTexture(background,NULL,NULL,&temp.w,&temp.h);
  //SDL_RenderCopy(renderer,background,NULL,&temp);
  BaseRenderer::Instance()->RenderTexture(background,screen,NULL,&temp);
  if(surfaces.size()<=end)
    end=surfaces.size();
  
  for(int i=start; i>end; i--)
    {
      temp.x=posx+startx;
      temp.y=posy+starty+(i+1)*TTF_FontHeight(font);
      SDL_QueryTexture(surfaces[i],NULL,NULL,&temp.w,&temp.h);
      //SDL_RenderCopy(renderer,surfaces[i],NULL,&temp);
      BaseRenderer::Instance()->RenderTexture(surfaces[i],screen,NULL,&temp);
    }
  
}


void InfoSurface::setStart(int x,int y)
{
    this->startx=x;
    this->starty=y;
}


void InfoSurface::setposition(int x,int y)
{
    this->posx=x;
    this->posy=y;
}

void InfoSurface::ChangeEntry(int i,string newEnt)
{
    text[i]=newEnt;
    SDL_DestroyTexture(surfaces[i]);
    SDL_Surface *new_surf=TTF_RenderText_Solid(font,newEnt.c_str(),SDL_Color {0,0,0});
    surfaces[i]=SDL_CreateTextureFromSurface(  BaseRenderer::Instance()->Renderer(), new_surf );
    SDL_FreeSurface(new_surf);
}


void InfoSurface::ChangeEntry(int i,string newEnt,unsigned char  r,unsigned char g,unsigned char b)
{
    text[i]=newEnt;
    SDL_DestroyTexture(surfaces[i]);
        SDL_Surface *new_surf=TTF_RenderText_Solid(font,newEnt.c_str(),SDL_Color {r,g,b});
    surfaces[i]=SDL_CreateTextureFromSurface(  BaseRenderer::Instance()->Renderer(), new_surf );
    SDL_FreeSurface(new_surf);
}

int InfoSurface::getSize()
{
    return surfaces.size();

}
