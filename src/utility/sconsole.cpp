#include "sconsole.h"


SConsole::SConsole(int width,int height,int r,int g,int b,int a,TTF_Font *font)
{
  this->surf=new InfoSurface(width,height,r,g,b,a,font);
    active=false;
    fontheight=TTF_FontHeight(font);
    this->height=height;
    this->cur=0;
}

SConsole::~SConsole()
{
  delete surf;
}

void SConsole::Show(SDL_Texture *screen)
{

    surf->Show(screen,height/fontheight);
}

void SConsole::Handle_Input(SDL_Event event)
{
    if(event.key.keysym.sym==SDLK_RETURN)
    {
        surf->AddText(sio.getString(),tr,tg,tb);
        sio.clear();
    }
    else
    {
        sio.addChar(event);

    }
    if(surf->getSize()>0)
        surf->ChangeEntry(surf->getSize()-1,sio.getString(),tr,tg,tb);
    else
        surf->AddText(sio.getString(),tr,tg,tb);



}

void SConsole::SetActive(bool a)
{
    this->active=a;
}
bool SConsole::IsActive()
{
    return this->active;
}


void SConsole::Scroll()
{
    /*if(surf->getSize()%height/fontheight==0)
    cur++;
    */
}
void SConsole::setTextColor(int r,int g,int b)
{

    tr=r;
    tg=g;
    tb=b;
}
void SConsole::Print(string text)
{
    surf->AddText(text,0,0,0);

}
