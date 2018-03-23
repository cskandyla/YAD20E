#include "InfoSurface.h"
#include "Stringio.h"

#ifndef __SCONSOLE__
#define __SCONSOLE__
class SConsole
{
protected:
    InfoSurface *surf;
    StringIO sio;
    bool active;
    int fontheight;
    int height;
    int cur;
    int tr,tg,tb;

public:
    SConsole(int width,int height,int r,int g,int b,int a,TTF_Font *font);
    virtual ~SConsole();
    void Print(string text);
    void Handle_Input(SDL_Event event);
    void Scroll();
    void Show(SDL_Texture *screen);
    void SetActive(bool a);
    bool IsActive();
    void setTextColor(int r,int g, int b);
};
#endif
