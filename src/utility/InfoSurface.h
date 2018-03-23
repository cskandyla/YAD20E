#include <vector>
#include <deque>
#include "SDL2/SDL.h"
#include "SDL2/SDL_ttf.h"
#include <string>
using namespace std;

#ifndef __INFOSURFACE__
#define __INFOSURFACE__
class InfoSurface
{
private:
    SDL_Texture *background;
    deque<string> text;
    deque<SDL_Texture*> surfaces;
    int startx,starty;
    int posx, posy;
    TTF_Font *font;
public:
    InfoSurface(char *backgroundimage,TTF_Font *font);
    InfoSurface(int width,int height,unsigned char r,unsigned char g,unsigned char b,int a,TTF_Font *font);
    virtual ~InfoSurface();
    void AddText(char *text,unsigned char r,unsigned char g,unsigned char b);
    void AddText(char *text);
    void AddText(string text);
    void AddText(string text,unsigned char r,unsigned char g,unsigned char b);
    void Show(SDL_Texture *screen);
    void Show(SDL_Texture *screen,int num);
    void Show(SDL_Texture *screen,int start,int end);
    void setStart(int x,int y);
    void setposition(int x,int y);
    void ChangeEntry(int i,string newEnt);
    void ChangeEntry(int i,string newEnt,unsigned char r,unsigned char g,unsigned char b);
    int getSize();
};
#endif
