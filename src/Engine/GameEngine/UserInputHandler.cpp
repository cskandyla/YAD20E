#include "UserInputHandler.h"
#include "CellInfo.h"
#include "params.h"
#include "MapIndex.h"
#include "Turn.h"
#include "Astar.h"
#include "Camera.h"
#include <iostream>
using std::cout;
using std::endl;


UserInputHandler::UserInputHandler(Camera *camera,Turn *the_turn)
{
  this->camera=camera;
  this->the_turn=the_turn;
  this->i_state=NULL;
  
}

UserInputHandler::~UserInputHandler()
{
  if(i_state)
    delete i_state;
}


void UserInputHandler::HandleEvents(SDL_Event *event)
{
  {

    switch (event->type)
      {
      case SDL_KEYDOWN:
	{
	  if (event->key.keysym.sym == SDLK_ESCAPE)
	    {
	      cout<<"Exiting"<<endl;
	      exit(0);
	    }
	  else if(event->key.keysym.sym == SDLK_UP)
	    {
	      if(!the_turn->AIControlled() && !i_state)
		{
		  the_turn->TheCharacter()->SetDirection(UP);
		}
	    }
	  else if(event->key.keysym.sym == SDLK_DOWN)
	    {
	      if(!the_turn->AIControlled() && !i_state)
		{
		  the_turn->TheCharacter()->SetDirection(DOWN);
		}
	    }
	  else if(event->key.keysym.sym == SDLK_LEFT)
	    {
	      if(!the_turn->AIControlled() && !i_state)
		{
		  the_turn->TheCharacter()->SetDirection(LEFT);
		}
	    }
	  else if(event->key.keysym.sym == SDLK_RIGHT)
	    {
	      if(!the_turn->AIControlled() && !i_state)
		{
		  the_turn->TheCharacter()->SetDirection(RIGHT);
		}
	    }
	}
	break;
      case SDL_MOUSEBUTTONDOWN :
	{
	  if(event->button.button == SDL_BUTTON_LEFT)
	    {   
	      LeftClick(event);	  
	    }
	  else if(event->button.button == SDL_BUTTON_RIGHT)
	    {
	      RightClick(event);
	    }

	}
	break; 
      }
  }
}


void UserInputHandler::SetState(InputState *i_state)
{
  if(!the_turn->AIControlled())
    {
      if(this->i_state)
	delete this->i_state;
      this->i_state=i_state;
    }
}

InputState* UserInputHandler::GetState()
{
  return this->i_state;
}

void UserInputHandler::LeftClick(SDL_Event *event)
{

  int xpos=event->button.x;
  int ypos=event->button.y;
  if(i_state==NULL)
    {
      
      CellInfo *cell=camera->ClickedCell(xpos,ypos);
      if(!cell)
	{
	  //Clicked On Empty Space
	  ClickedOnEmptySpace(camera->ClickedRect(xpos,ypos));
	}
      else if(cell)
	{
	  switch (cell->getType())
	    {
	    case CHARACTER_T:
	      ClickedOnCharacter(cell);
	      break;
	    case OBJECT_T:
	      ClickedOnObject(cell);
	      break;
	    }
	}
  
    }
  else
    {
	    if(i_state)
	    {
		    i_state->Execute(camera->Translate(xpos,ypos));
		    if(i_state->IsDone())
		    {
			    delete i_state;
			    i_state=NULL;
		    }
	    }
    }
  
}
void UserInputHandler::ClickedOnEmptySpace(SDL_Rect cellrect)
{
  //maybe show tile info?
}

void UserInputHandler::ClickedOnCharacter(CellInfo *cellinfo)
{
  //Show character info?
}


void UserInputHandler::ClickedOnObject(CellInfo *cellinfo)
{
  
}

void UserInputHandler::RightClick(SDL_Event *event)
{
  //Handle the right click menu
  if(this->i_state)
    delete this->i_state;
  this->i_state=NULL;

}
