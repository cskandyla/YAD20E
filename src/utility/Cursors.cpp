#include "Cursors.h"
#include "miscellaneous.h"



Cursor::Cursor(CURSOR_MODE cm,SDL_Surface *cursor_surf)
{
  cursors[cm]=cursor_surf;
  this->cursor_surf=cursor_surf;
}
void Cursor::Add(CURSOR_MODE cm,SDL_Surface *cursor_surf)
{
  cursors[cm]=cursor_surf;
}

bool Cursor::SetMode(CURSOR_MODE cm)
{

  if(cursors.find(cm)!=cursors.end())
    {
      cursor_surf=cursors[cm];
      return true;
    }
  return false;
}

void Cursor::Draw(int x,int y,SDL_Surface *screen)
{
  SDL_Rect pos;
  pos.x=x;
  pos.y=y;
  SDL_BlitSurface(cursor_surf,NULL,screen,&pos);
}


