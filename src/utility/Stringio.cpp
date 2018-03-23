#include "Stringio.h"

StringIO::StringIO()
{

}


void StringIO::addChar(SDL_Event event)
{
    if(event.key.keysym.sym>='a' && event.key.keysym.sym<=SDLK_z && event.key.keysym.mod & KMOD_LSHIFT)
    {
        text+=event.key.keysym.sym-32;
    }
    else if(event.key.keysym.sym>='a' && event.key.keysym.sym<=SDLK_z )
    {
        text+=event.key.keysym.sym;
    }





    else if(event.key.keysym.sym==SDLK_SPACE)
        text+=' ';
    else if(event.key.keysym.sym==SDLK_EQUALS)
      text+='=';
     else if(event.key.keysym.sym==SDLK_SEMICOLON && event.key.keysym.mod & KMOD_LSHIFT)
        text+=':';
    else if(event.key.keysym.sym==SDLK_MINUS && event.key.keysym.mod & KMOD_LSHIFT)
        text+='_';
    else if(event.key.keysym.sym==SDLK_9  && event.key.keysym.mod & KMOD_LSHIFT)
        text+='(';
    else if(event.key.keysym.sym==SDLK_0  && event.key.keysym.mod & KMOD_LSHIFT)
        text+=')';
    else if(event.key.keysym.sym==SDLK_QUOTE  && event.key.keysym.mod & KMOD_LSHIFT)
        text+='"';
    else if(event.key.keysym.sym==SDLK_QUOTE  )
        text+='\'';
    else if(event.key.keysym.sym==SDLK_SLASH  && event.key.keysym.mod & KMOD_LSHIFT)
        text+='?';
    else if(event.key.keysym.sym==SDLK_SLASH  )
        text+='/';
    else if(event.key.keysym.sym==SDLK_SEMICOLON)
        text+=';';
    else if(event.key.keysym.sym==SDLK_PERIOD)
        text+='.';
    else if(event.key.keysym.sym==SDLK_COMMA)
        text+=',';
    else if( ( event.key.keysym.sym >= '0' ) && ( event.key.keysym.sym <= '9' ) )
    {

        text += event.key.keysym.sym;
    }
    else if(event.key.keysym.sym==SDLK_BACKSPACE && text.length()>=1)
    {
        text.erase(text.length()-1);
    }

}
string StringIO::getString()
{
    return text;
}

void StringIO::clear()
{
    this->text.erase(text.begin(),text.end());
}
