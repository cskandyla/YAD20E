#include "Button.h"
#include <iostream>
#include "BaseRenderer.h"

Button::Button(string name,SDL_Rect pos,string image):name(name)
{
  SDL_Texture *img=BaseRenderer::Instance()->LoadImage(image);
  if(img==NULL)
    {
      //FREAK OUT
    }

  SDL_Rect rect;
  rect.x=pos.x;
  rect.y=pos.y;
  int w,h;
  SDL_QueryTexture(img, NULL, NULL, &w, &h);
  rect.w=w;
  rect.h=h;
  button_inner.first=rect;
  button_inner.second=img;
  clicked=false;
  visible=true;
  ButtonAction=NULL;
  data=NULL;
  background=NULL;
  dealloc=true;
  bgdealloc=false;
    
}
Button::Button(string name,SDL_Rect pos,string image,void (*ButtonAction)(void *data),void *data):name(name)
{

  SDL_Texture *img=BaseRenderer::Instance()->LoadImage(image);
  if(img==NULL)
    {
      //FREAK OUT

    }
  SDL_Rect rect;
  rect.x=pos.x;
  rect.y=pos.y;
  int w,h;
  SDL_QueryTexture(img, NULL, NULL, &w, &h);
  rect.w=w;
  rect.h=h;
  button_inner.first=rect;
  button_inner.second=img;
  this->ButtonAction=ButtonAction;
  this->data=data;
  this->clicked=false;
  this->visible=true;
  background=NULL;
  dealloc=true;
  bgdealloc=false;
}

Button::Button(string name, SDL_Rect pos,SDL_Texture *surf):name(name)
{
  SDL_Rect rect;
  rect.x=pos.x;
  rect.y=pos.y;
  int w,h;
  SDL_QueryTexture(surf, NULL, NULL, &w, &h);
  rect.w=w;
  rect.h=h;
  button_inner.first=rect;
  button_inner.second=surf;
  this->clicked=false;
  this->visible=true;
  background=NULL;
  ButtonAction=NULL;
  data=NULL;
  dealloc=false;
  bgdealloc=false;
}

Button::~Button()
{
  if(dealloc)
    SDL_DestroyTexture(button_inner.second);
  if(data)
    //delete data;
    if(bgdealloc)
      if(background)
	SDL_DestroyTexture(background);
  
}

void Button::Show(bool flag)
{
  this->visible=flag;
}

SDL_Rect Button::GetRect()
{
  
  return button_inner.first;
}
void Button::SetPosition(int x,int y)
{
  this->button_inner.first.x=x;
  this->button_inner.first.y=y;
}

string Button::GetName()
{
  return name;
}

SDL_Texture* Button::GetImage()
{
  return this->button_inner.second;
}

bool Button::Clicked(int x,int y)
{
  if(visible)
    if(x < button_inner.first.w+button_inner.first.x && x > button_inner.first.x && y < button_inner.first.h+button_inner.first.y && y > button_inner.first.y)
      {
        clicked=true;
        return true;
      }

  return false;
}

bool Button::WasClicked()
{
  return clicked;
}

void Button::Activate()
{
  if(ButtonAction)
    this->ButtonAction(data);
}
  
void Button::Draw(SDL_Texture *screen)
{
  if(visible)
    {
      
      // SDL_BlitSurface(button_inner.second, NULL, screen, &button_inner.first);
      
      BaseRenderer::Instance()->RenderTexture(button_inner.second,screen,NULL,&button_inner.first);
      if(background)
	//SDL_BlitSurface(background, NULL, screen, &button_inner.first);
	BaseRenderer::Instance()->RenderTexture(background,screen,NULL,&button_inner.first);


    }
}

void Button::SetAction(void (*ButtonAction)(void*),void *data)
{
  this->ButtonAction=ButtonAction;
  this->data=data;
}

void Button::SetBackground(SDL_Texture *background)
{
  if(bgdealloc)
  if(this->background)
    SDL_DestroyTexture(this->background);
  this->background=background;
  bgdealloc=false;
}
void Button::SetBackground(string backgroundimage)
{

  SDL_Texture *img=BaseRenderer::Instance()->LoadImage(backgroundimage.c_str());
  if(img==NULL)
    {
      //FREAK OUT
    }
    if(bgdealloc)
  if(this->background)
    SDL_DestroyTexture(this->background);
  this->background=img;
  bgdealloc=true;
}
