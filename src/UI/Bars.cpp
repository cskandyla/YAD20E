#include "Bars.h"
#include "TurnEngine.h"
#include "Camera.h"
#include "Mage.h"
#include "UsableItem.h"
#include "InputState.h"
#include "UserInputHandler.h"
#include "BaseRenderer.h"
#include <iostream>
using  std::cout;
using  std::endl;

UI_Bars::UI_Bars(TurnEngine *t_e,Camera *camera,string path_move,string path_attack,string path_use,string path_abilities,string path_items,string path_end):t_e(t_e),camera(camera)
{
  basemenu=new ButtonMenu(O_RIGHT,SDL_Rect{0,108,0,0});
  basemenu->Add("Move",path_move);
  basemenu->Add("Attack",path_attack);
  basemenu->Add("Use",path_use);
  basemenu->Add("Abilities",path_abilities);
  basemenu->Add("Inventory",path_items);
  basemenu->Add("Close",path_end);
  basemenu->Show(true);
  attack=new ButtonMenu(O_RIGHT,SDL_Rect{0,0,32,0});
  attack->Show(false);
  abilities=new ButtonMenu(O_RIGHT,SDL_Rect{0,32,0,0});
  abilities->Show(false);
  items=new ButtonMenu(O_RIGHT,SDL_Rect{0,32,0,0});
  items->Show(false);
}

UI_Bars::~UI_Bars()
{
  delete basemenu;
  delete attack;
  delete abilities;
  delete items;
  
}

Camera* UI_Bars::GetCamera()
{
  return this->camera;
}

void UI_Bars::Add(MENU_T menu,Button* button)
{
  if(menu==ATTACK_MENU)
    {
      attack->Add(button);
    }
  else if(menu==ABILITY_MENU)
    {
      abilities->Add(button);
    }
  else if(menu==ITEM_MENU)
    {
      items->Add(button);
    }
}


void UI_Bars::HandleEvents(SDL_Event *event)
{
  switch (event->type)
    {
    case SDL_MOUSEBUTTONDOWN :
      {
	pair<int,int> pos=camera->Translate(event->button.x,event->button.y);
	  
	if(event->button.button == SDL_BUTTON_LEFT)
	  {
	      
	    Button *button=basemenu->Clicked(pos.first,pos.second);
	    if(button)
	      {
		      HandleBaseMenu(button);
	      }
	    button=attack->Clicked(pos.first,pos.second);
	    if(button)
	      {
		HandleAttackMenu(button);
	      }
	    button=abilities->Clicked(pos.first,pos.second);
	    if(button)
	      {
		HandleAbilitiesMenu(button);
	      }
	    button=items->Clicked(pos.first,pos.second);
	    if(button)
	      {
		HandleItemMenu(button);
	      }
	  }
      }
      break; 
    }
}

void UI_Bars::HandleBaseMenu(Button *button)
{
	if(t_e->GetTurn() && !t_e->GetTurn()->AIControlled())
    {
	    if(button->GetName()=="Close")
	{
	  attack->Show(false);
	  abilities->Show(false);
	  items->Show(false);
	  t_e->GetTurn()->SetDone(true);
	  
	}
      else if(button->GetName()=="Move")
	{
	  attack->Show(false);
	  abilities->Show(false);
	  items->Show(false);
	  if (t_e->GetTurn() &&  !(t_e->GetTurn()->StandardActionDone() && t_e->GetTurn()->HasMoved()))
	    t_e->GetTurn()->GetUserInputHandler()->SetState(new MoveState(t_e->GetTurn()));
	}
      else if(button->GetName()=="Abilities")
	{
	  attack->Show(false);
	  abilities->Show(true);
	  items->Show(false);
      
	}
      else if(button->GetName()=="Attack")
	{
		if (t_e->GetTurn() && !t_e->GetTurn()->StandardActionDone())
	    t_e->GetTurn()->GetUserInputHandler()->SetState(new AttackState(t_e->GetTurn()));
	}
      else if(button->GetName()=="Inventory")
	{
	  cout<<"Item BASE MENU"<<endl;
	  attack->Show(false);
	  abilities->Show(false);
	  items->Show(true);
	  CheckItems();
	}
      else if(button->GetName()=="Use")
      {
	      attack->Show(false);
	      abilities->Show(false);
	      items->Show(false);
	      if (t_e->GetTurn() && !t_e->GetTurn()->StandardActionDone())
	      {
		      cout<<"Use Action Menu"<<endl;
		      t_e->GetTurn()->GetUserInputHandler()->SetState(new UseState(t_e->GetTurn()));
	      }
      }
    }
}

void UI_Bars::HandleAttackMenu(Button *button)
{
	if (t_e->GetTurn() && !t_e->GetTurn()->StandardActionDone())
    t_e->GetTurn()->GetUserInputHandler()->SetState(new AttackState(t_e->GetTurn()));
   
}
void UI_Bars::HandleAbilitiesMenu(Button *button)
{

	
/*
if(spell_list->Shown())
{
	BuildSpellMenu();
	//Update our spells
	spell_interface->UpdatePreparedSpells();
}

bool sp_shown=spell_list->Shown();
sp_shown=!sp_shown;
spell_list->Show(sp_shown);
*/		  
}
void UI_Bars::HandleItemMenu(Button *button)
{
  cout<<"Item MENU"<<endl;
  if (t_e->GetTurn()  && !t_e->GetTurn()->StandardActionDone())
    UseItem(button);
}

void UI_Bars::Draw(SDL_Texture *screen)
{
  SDL_SetRenderTarget(BaseRenderer::Instance()->Renderer(),screen);
  SDL_RenderClear(BaseRenderer::Instance()->Renderer());
  if(basemenu && basemenu->Shown())
    {
      basemenu->Draw(screen);
    }
  if(attack && attack->Shown())
    {
      attack->Draw(screen);
    }
  else if(abilities && abilities->Shown())
    {
      abilities->Draw(screen);
    }
  else if(items && items->Shown())
    {
      items->Draw(screen);
    }
}

void UI_Bars::CheckItems()
{
	if(!t_e->GetTurn())
		return;
  items->Clear();
  BaseCharacter *chara=t_e->GetTurn()->TheCharacter();
  vector<Item*> c_items=chara->getInventory();
  for(int i=0;i<c_items.size();i++)
    {
      if(dynamic_cast<UsableItem*>(c_items[i]))
	{
	  items->Add(new Button(c_items[i]->getInfo()->getName(),SDL_Rect{0,0,32,32},c_items[i]->getIcon()));
	}
    }
}

void UI_Bars::SpellCast(Button *button)
{
	if(t_e->GetTurn())
  t_e->GetTurn()->GetUserInputHandler()->SetState(new SpellState(t_e->GetTurn(),button->GetName()));
}


void UI_Bars::UseItem(Button *button)
{
	if(t_e->GetTurn())
  t_e->GetTurn()->GetUserInputHandler()->SetState(new ItemState(t_e->GetTurn(),button->GetName()));
}

ButtonMenu* UI_Bars::GetMenu(MENU_T menu)
{
  if(menu==BASE_MENU)
    {
      return basemenu;
    }
  else if(menu==ATTACK_MENU)
    {
      return attack;
    }
  else if(menu==ABILITY_MENU)
    {
      return abilities;
    }
  else if(menu==ITEM_MENU)
    {
      return  items;
    }
  return NULL;
}
