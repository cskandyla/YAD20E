#include "Label.h"

SimpleLabel::SimpleLabel(string label_text,TTF_Font *font)
{
  SDL_Color c;
  c.r=0;
  c.g=0;
  c.b=0;
  label_surf=TTF_RenderText_Solid(font,label_text.c_str(),c);
}

SimpleLabel::~SimpleLabel()
{
  SDL_FreeSurface(label_surf);
}
void SimpleLabel::Draw(int x,int y,SDL_Surface *screen)
{

  SDL_Rect pos;
  pos.x=x;
  pos.y=y;
  SDL_BlitSurface(label_surf,NULL,screen,&pos);
}
