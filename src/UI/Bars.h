#include <SDL2/SDL.h>
#include "ButtonMenu.h"
#include "OptionsMenu.h"



#ifndef __UI_BARS_H_
#define __UI_BARS_H_
//ADD SPELLS / INVENTORY / ATTACK /
enum MENU_T{BASE_MENU,ATTACK_MENU,ABILITY_MENU,ITEM_MENU};
class Camera;
class TurnEngine;
class UI_Bars
{
private:

ButtonMenu *basemenu;
//  OptionsMenu optionsmenu;//Spells/Fighter --wuteva--/
ButtonMenu *attack,*abilities,*items;
TurnEngine *t_e;
Camera *camera;

public:
//Constructor
	UI_Bars(TurnEngine *t_e,Camera *camera,string path_move,string path_attack,string path_use,string path_abilities,string path_items,string path_end);
 virtual ~UI_Bars();
 //Add/Remove Menu Elements
 void Add(MENU_T menu,Button* button);
 void Remove(MENU_T menu,string button);
 ButtonMenu* GetMenu(MENU_T menu);
 
 
 //Event Handling
 virtual void HandleEvents(SDL_Event *event);
 void HandleBaseMenu(Button *button);
 void HandleAttackMenu(Button *button);
 void HandleAbilitiesMenu(Button *button);
 void HandleItemMenu(Button*button);

 //virtual move to MageBars when implemented
 void SpellCast(Button *button);
 void UseItem(Button *button);


 //Camera for event handling
 Camera* GetCamera();
 // Check for new items
 void CheckItems();
 
//Drawing
virtual void Draw(SDL_Texture *screen);
};


#endif
