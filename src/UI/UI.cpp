#include "UI.h"
#include "TurnEngine.h"
#include "SpellList.h"
#include "SpellInterface.h"
//#include "CharacterSheet.h"
#include "Bars.h"
#include "Camera.h"
#include "Colision.h"
#include "KnowledgePool.h"
#include "BaseRenderer.h"
#include "InspectWindow.h"
#include "UserInputHandler.h"

UI::UI(TurnEngine *t_e,Camera *camera,TTF_Font *font)
{
	this->t_e=t_e;
  //Place The portrait if it exists for coolness
  menubars=new UI_Bars(t_e,camera,
		       "Resources/UI/Buttons/move.png",
		       "Resources/UI/Buttons/attack.png",
		       "Resources/UI/Buttons/hand.png",
		       "Resources/UI/Buttons/tome.png",
		       "Resources/UI/Buttons/backpack.png",
		       "Resources/UI/Buttons/x.png");
  //  char_sheet=new CharacterSheet(font,KnowledgePool::Instance()->getCharacter(1),"Resources/UI/Backgrounds/character_sheet_background.png");
  spell_list=new SpellList(font,dynamic_cast<Caster*>(KnowledgePool::Instance()->getCharacter(1)));
  portrait=KnowledgePool::Instance()->getCharacter(1)->GetPortrait();
  spell_interface=new SpellInterface(t_e,dynamic_cast<Caster*>(KnowledgePool::Instance()->getCharacter(1)),camera,SDL_Rect{384,48,0,0});
  inspect_window=new InspectWindow(font,SDL_Rect{600,0,0,0},t_e->GetCamera());

  menubars->GetMenu(BASE_MENU)->SetBackground("Resources/UI/Buttons/boxNormal.png");
  menubars->GetMenu(ABILITY_MENU)->SetBackground("Resources/UI/Buttons/frame3.png");
  menubars->GetMenu(ITEM_MENU)->SetBackground("Resources/UI/Buttons/boxNormal.png");

  BuildSpellMenu();
  BuildItemMenu();
  
}

UI::~UI()
{
  delete menubars;
  delete spell_list;
  //  delete char_sheet;
  delete spell_interface;
}

void UI::Update()
{
	inspect_window->Update();
}

void UI::Draw(SDL_Texture *game_screen,SDL_Texture *toolbox_surf)
{
  if(spell_list->Shown())
    spell_list->Draw(game_screen);
  //  else if(char_sheet->Shown())
  //char_sheet->Draw(game_screen);
  menubars->Draw(toolbox_surf);
  spell_interface->Draw(toolbox_surf);
  inspect_window->Draw(toolbox_surf);
  int tool_w,tool_h;
  //SDL_QueryTexture(toolbox_surf,NULL,NULL,&tool_w,&tool_h);
  //SDL_Rect portrait_pos{(short)(toolbox_surf->w-portrait->w),0,0,0};
  //  SDL_BlitSurface(portrait,NULL,toolbox_surf,&portrait_pos);
  //  SDL_RenderCopy(renderer,portrait,NULL,&portrait_pos);
  //  BaseRenderer::Instance()->RenderTexture(portrait,toolbox_surf,NULL,&portrait_pos);
  
}

bool UI::Shown()
{
  int xpos,ypos;
   SDL_GetMouseState(&xpos, &ypos);
//   if(spell_list->Shown() /*|| char_sheet->Shown()*/ /*|| Colision::PointInRect(pair<int,int>(xpos,ypos),*menubars->GetCamera()->GetCam())*/ )
    return true;
  return false;
}


void UI::HandleEvents(SDL_Event *event)
{
  if(spell_list->Shown())
    {
      spell_list->HandleEvents(event);
    }
    {
      switch (event->type)
	{
	case SDL_KEYDOWN:
	  {
	    if(event->key.keysym.sym==SDLK_p)
	      {	      
	    	    if(spell_list->Shown())
		      {
			BuildSpellMenu();
			//Update our spells
			spell_interface->UpdatePreparedSpells();
			}
		    
		    bool sp_shown=spell_list->Shown();
		    sp_shown=!sp_shown;
		    spell_list->Show(sp_shown);
		    
	      }
	    break;
	  }
	case SDL_MOUSEBUTTONDOWN:
	  {
	    int xpos=event->button.x;
	    int ypos=event->button.y;
	    if(Colision::PointInRect(pair<int,int>(xpos,ypos),*menubars->GetCamera()->GetCam()))
	      {
		menubars->HandleEvents(event);
		spell_interface->HandleEvents(event);
	      }
	    if(t_e->GetTurn() &&  (!t_e->GetTurn()->GetUserInputHandler() || !t_e->GetTurn()->GetUserInputHandler()->GetState()))
	    {
	    inspect_window->HandleEvents(event);
	    }
	  }
	  break;
	}
    }
}

void UI::BuildSpellMenu()
{
  menubars->GetMenu(ABILITY_MENU)->Clear();
  vector<ButtonMenu*> spell_menu=spell_list->GetPrepared();
  for(int i=0;i<spell_menu.size();i++)
    {
      for(int j=0;j<spell_menu[i]->GetButtons().size();j++)
	{
	  //Copying into a new container
	  menubars->Add(ABILITY_MENU,new Button(spell_menu[i]->GetButtons()[j]->GetName(),SDL_Rect{0,0,0,0},(spell_menu[i]->GetButtons()[j]->GetImage())));
	}

    }
}

void UI::BuildItemMenu()
{
  menubars->GetMenu(ITEM_MENU)->Clear();
  vector<Item*> items=KnowledgePool::Instance()->getCharacter(1)->getInventory();
  for(int i=0;i<items.size();i++)
    {
      menubars->Add(ABILITY_MENU,new Button(items[i]->getInfo()->getName(),SDL_Rect{0,0,0,0},items[i]->getIcon()));
    }
}


