#include "ScriptConsole.h"


void ScriptConsole::Handle_Input(SDL_Event event)
{
    if(event.key.keysym.sym==SDLK_RETURN)
    {
        surf->AddText(sio.getString(),tr,tg,tb);
        Sh->CallHandler(sio.getString().c_str());
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


ScriptConsole::~ScriptConsole()
{
}
