#include "ButtonMenu.h"
#include "BaseRenderer.h"
#include <iostream>
using std::cout;
using std::endl;

ButtonMenu::ButtonMenu(Orientation orient,SDL_Rect starting_pos):orient(orient),starting_pos(starting_pos)
{
  background=NULL;
  visible=true;
}
void ButtonMenu::Add(string name,string image)
{
  cout<<"Starting Pos:"<<starting_pos.x<<','<<starting_pos.y<<endl;
  SDL_Rect next_pos;;
  if(orient==O_RIGHT)
    {
      if(buttons.size()>0)
	next_pos.x=buttons[buttons.size()-1]->GetRect().x+buttons[buttons.size()-1]->GetRect().w;
      else
	next_pos.x=starting_pos.x;
      next_pos.y=starting_pos.y;
    }
 else
    {
      int w=0,h=0;
      if(background)
	{
	  SDL_QueryTexture(background,NULL,NULL,&w,&h);
	}

      if(buttons.size()>0)
	{
	  
	  if(background)
	    next_pos.y=buttons[buttons.size()-1]->GetRect().y+h;
	  else
	    next_pos.y=buttons[buttons.size()-1]->GetRect().y+buttons[buttons.size()-1]->GetRect().h;
	}
      else
	next_pos.y=starting_pos.y;
	next_pos.x=starting_pos.x;

    }
  buttons.push_back(new Button(name,next_pos,image));
  if(background)
    buttons[buttons.size()-1]->SetBackground(background);

}

ButtonMenu::~ButtonMenu()
{

  for(int i=0;i<buttons.size();i++)
    {
      delete buttons[i];
    }
  if(background)
  SDL_DestroyTexture(background);

}


void ButtonMenu::Add(string name,string image,void (*ButtonAction)(void*),void *data)
{
  SDL_Rect next_pos;;
        int w=0,h=0;
      if(background)
	{
	  SDL_QueryTexture(background,NULL,NULL,&w,&h);
	}
  if(orient==O_RIGHT)
    {
      if(buttons.size()>0)
	{
	  if(background)
	    next_pos.x=buttons[buttons.size()-1]->GetRect().x+w;
	  else
	    next_pos.x=buttons[buttons.size()-1]->GetRect().x+buttons[buttons.size()-1]->GetRect().w;
	}
      else
	next_pos.x=starting_pos.x;
      next_pos.y=starting_pos.y;
    }
  else
    {
      next_pos.x=starting_pos.x;
      if(buttons.size()>0)
	{
	  if(background)
	    next_pos.x=buttons[buttons.size()-1]->GetRect().x+w;
	  else
	    next_pos.x=buttons[buttons.size()-1]->GetRect().x+buttons[buttons.size()-1]->GetRect().w;
	}
      else
	next_pos.y=starting_pos.y;

    }
  buttons.push_back(new Button(name,next_pos,image,ButtonAction,data));
    if(background)
    buttons[buttons.size()-1]->SetBackground(background);

}

void ButtonMenu::Add(string name,SDL_Texture *surf)
{
  cout<<"Starting Pos:"<<starting_pos.x<<','<<starting_pos.y<<endl;
   SDL_Rect next_pos;;
         int w=0,h=0;
      if(background)
	{
	  SDL_QueryTexture(background,NULL,NULL,&w,&h);
	}
  if(orient==O_RIGHT)
    {
      if(buttons.size()>0)
	{
	if(background)
	    next_pos.x=buttons[buttons.size()-1]->GetRect().x+w;
	  else
	    next_pos.x=buttons[buttons.size()-1]->GetRect().x+buttons[buttons.size()-1]->GetRect().w;
	}
      else
	{
	  
	next_pos.x=starting_pos.x;
	
	}
      next_pos.y=starting_pos.y;
    }
  else
    {
      next_pos.x=starting_pos.x;
      if(buttons.size()>0)	
	next_pos.x=buttons[buttons.size()-1]->GetRect().x+buttons[buttons.size()-1]->GetRect().w;
      else
	next_pos.y=starting_pos.y;

    }
  buttons.push_back(new Button(name,next_pos,surf));
    if(background)
    buttons[buttons.size()-1]->SetBackground(background);
}

void ButtonMenu::Add(Button *button)
{
  SDL_Rect next_pos;

        int w=0,h=0;
      if(background)
	{
	  SDL_QueryTexture(background,NULL,NULL,&w,&h);
	}
if(orient==O_RIGHT)
    {
      if(buttons.size()>0)
	{
	  if(background)
	    next_pos.x=buttons[buttons.size()-1]->GetRect().x+w;
	  else
	    next_pos.x=buttons[buttons.size()-1]->GetRect().x+buttons[buttons.size()-1]->GetRect().w;
	}
      else
	next_pos.x=starting_pos.x;
      next_pos.y=starting_pos.y;
    }
  else
    {
      next_pos.x=starting_pos.x;
      if(buttons.size()>0)	
	next_pos.x=buttons[buttons.size()-1]->GetRect().x+buttons[buttons.size()-1]->GetRect().w;
      else
	next_pos.y=starting_pos.y;
    }
 button->SetPosition(next_pos.x,next_pos.y);

 buttons.push_back(button);
   if(background)
    buttons[buttons.size()-1]->SetBackground(background);
}

void ButtonMenu::Remove(Button *button)
{
  int found=-1;
  for(int i=0;i<buttons.size();i++)
    {
      if(buttons[i]->GetName().compare(button->GetName())==0)
	{
	  //buttons.erase(buttons.begin()+i);
	  found=i;
	}
    }
  if(found!=-1)
    {
      buttons.erase(buttons.begin()+found);
    }
}

void ButtonMenu::Clear()
{

  
  for(int i=0;i<buttons.size();i++)
    {
      delete buttons[i];
      }

  buttons.clear();
}

void ButtonMenu::Draw(SDL_Texture *screen)
{
  if(visible)
  for(int i=0;i<buttons.size();i++)
    {
      buttons[i]->Draw(screen);
    }
  
}

Button* ButtonMenu::Clicked(int x,int y)
{
  if(visible)
  for(int i=0;i<buttons.size();i++)
    {
      if(buttons[i]->Clicked(x,y))
	return buttons[i];
    }

  return NULL;
}

void ButtonMenu::Show(bool visible)
{
  this->visible=visible;
}

bool ButtonMenu::Shown()
{
  return this->visible;
}

void ButtonMenu::SetBackground(SDL_Texture *background)
{
  this->background=background;

      for(int i=0;i<buttons.size();i++)
      {
	buttons[i]->SetBackground(background);
      }
}
void ButtonMenu::SetBackground(string backgroundimage)
{

  SDL_Texture *img=BaseRenderer::Instance()->LoadImage(backgroundimage);
    if(img==NULL)
    {
      //FREAK OUT
    }
    this->background=img;

    for(int i=0;i<buttons.size();i++)
      {
	buttons[i]->SetBackground(background);
      }
}

int ButtonMenu::size()
{
  return buttons.size();

}

vector<Button*>& ButtonMenu::GetButtons()
{
  return buttons;
}
