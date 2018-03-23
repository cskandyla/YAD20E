#include <SDL2/SDL.h>
#include "map.h"
#include "MapIndex.h"
#include "Camera.h"
#include "DrawableTile.h"
#include "Turn.h"
#include <utility>
using std::pair;
#ifndef __RENDERER
#define __RENDERER

class GameRenderer
{
private:
    int visibility;
    DrawableTile *cursor_tile,*available_tile;
    Camera *camera;
    
public:
    GameRenderer(int visibility,Camera *camera);
    virtual ~GameRenderer();
    void Draw(SDL_Rect center,SDL_Texture *screen,Turn *the_turn);
    void DrawDynamicEntities(int starti,int startj,SDL_Texture *screen);
    void ShowCursor(SDL_Texture *screen,Turn *the_turn);
};
#endif

