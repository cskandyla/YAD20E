#include <SDL2/SDL.h>
#include <string>
using namespace std;

#ifndef __STRINGIO__
#define __STRINGIO__
class StringIO
{
private:
    string text;
public:
    StringIO();
    void addChar(SDL_Event event);
    string getString();
    void clear();

};
#endif
