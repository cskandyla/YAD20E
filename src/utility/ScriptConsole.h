#include "sconsole.h"
#include "ScriptHandler.h"

class ScriptConsole:public SConsole
{
private:

    ScriptHandler *Sh;
public:
 ScriptConsole(int width,int height,int r,int g,int b,int a,TTF_Font *font,ScriptHandler *sh):SConsole(width,height,r,g,b,a,font),Sh(sh)
    {

    }
    virtual ~ScriptConsole();


    void Handle_Input(SDL_Event event);

};
