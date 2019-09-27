#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#ifndef __UI_H
#define __UI_H
class Camera;
//class CharacterSheet;
class UI_Bars;
class SpellList;
class SpellInterface;
class TurnEngine;
class InspectWindow;




class UI
{

private:
	UI_Bars *menubars;
	// CharacterSheet *char_sheet;
	SpellList *spell_list;//Switch to AbilityList
	SpellInterface *spell_interface;
	InspectWindow *inspect_window;
	SDL_Texture *portrait;
	TurnEngine *t_e;
public:
	UI(TurnEngine *t_e,Camera *camera,TTF_Font *font);
	virtual ~UI();
	void Draw(SDL_Texture *game_screen,SDL_Texture *toolbox_surf);
	void HandleEvents(SDL_Event *event);
	void Update();
	bool Shown();
	void BuildSpellMenu();
	void BuildItemMenu();
};


#endif
