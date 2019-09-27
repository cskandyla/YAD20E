#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <string>
using std::string;
using std::pair;

#ifndef __SIMPLE_LABEL_H
#define __SIMPLE_LABEL_H

class SimpleLabel
{
private:
	string label_text;
	SDL_Texture *background;
	TTF_Font *font;
public:
	SimpleLabel(string label_text,TTF_Font *font);
	virtual ~SimpleLabel();
	void Draw(int x,int y,SDL_Texture *screen);
	void Update(string new_text);
};

#endif
