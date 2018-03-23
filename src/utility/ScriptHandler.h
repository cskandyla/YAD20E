#ifndef __SCRIPT_HANDLER
#define __SCRIPT_HANDLER
#include "Game.h"

class Game;
class ScriptHandler
{
private:
    void (*handlerfuntion)(const char *s, Game *g);
    Game *game;

public:
    ScriptHandler(void (*handlerfuntion)(const char *s, Game *g),Game *ga);
    void CallHandler(const char *s);





};
#endif // __SCRIPT_HANDLER
void Defaulthandler(const char *s,Game *g);
