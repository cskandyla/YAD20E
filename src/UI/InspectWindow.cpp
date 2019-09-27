#include "BaseRenderer.h"
#include "InspectWindow.h"
#include "KnowledgePool.h"
#include "params.h"
#include <iostream>

InspectWindow::InspectWindow(TTF_Font *font,SDL_Rect location,Camera *camera)
{
	this->font=font;
	textcolor.r=160;
	textcolor.g=0;
	textcolor.b=0;
	this->location=location;
	this->camera=camera;
	
	 

	
	target=KnowledgePool::Instance()->getCharacter(1);
	if(target)
	{
		if(target->getInfo())
		{
		SDL_Surface *namesurf=TTF_RenderText_Blended(font,target->getInfo()->getName().c_str(),textcolor);
		name_lbl=SDL_CreateTextureFromSurface( BaseRenderer::Instance()->Renderer(), namesurf);

		SDL_Surface *classsurf=TTF_RenderText_Blended(font,target->getInfo()->getClass().c_str(),textcolor);
		class_lbl=SDL_CreateTextureFromSurface( BaseRenderer::Instance()->Renderer(), classsurf);
		
		SDL_Surface *racesurf=TTF_RenderText_Blended(font,target->getInfo()->getRace().c_str(),textcolor);
		race_lbl=SDL_CreateTextureFromSurface( BaseRenderer::Instance()->Renderer(), racesurf);
		int hp=target->getGeneralStats()->getHp();
		string hp_string=std::to_string(target->getGeneralStats()->getHp())+'/'+std::to_string(target->getOriginalStats()->getHp());
		SDL_Surface *hpsurf=TTF_RenderText_Blended(font,hp_string.c_str(),textcolor);
		hp_lbl=SDL_CreateTextureFromSurface( BaseRenderer::Instance()->Renderer(),hpsurf );
		
		SDL_Surface *statussurf=TTF_RenderText_Blended(font,"Healthy",textcolor);
		status_lbl=SDL_CreateTextureFromSurface( BaseRenderer::Instance()->Renderer(), statussurf);
		}
	}
}


void InspectWindow::Draw(SDL_Texture *screen)
{
   SDL_Rect newpos;
  newpos.x=location.x;
  newpos.y=location.y;
  
  SDL_QueryTexture(name_lbl,NULL,NULL,&newpos.w,&newpos.h);
  BaseRenderer::Instance()->RenderTexture(name_lbl,screen,NULL,&newpos);
  newpos.x=location.x;
  newpos.y=location.y+newpos.h;
  SDL_QueryTexture(race_lbl,NULL,NULL,&newpos.w,&newpos.h);
  BaseRenderer::Instance()->RenderTexture(race_lbl,screen,NULL,&newpos);
  newpos.x=location.x+newpos.w+30;
  newpos.y=location.y+newpos.h;
  SDL_QueryTexture(class_lbl,NULL,NULL,&newpos.w,&newpos.h);
  BaseRenderer::Instance()->RenderTexture(class_lbl,screen,NULL,&newpos);
  newpos.x=location.x;
  newpos.y=location.y+2*newpos.h;
  SDL_QueryTexture(hp_lbl,NULL,NULL,&newpos.w,&newpos.h);
  BaseRenderer::Instance()->RenderTexture(hp_lbl,screen,NULL,&newpos);
  newpos.x=location.x;
  newpos.y=location.y+3*newpos.h;
  SDL_QueryTexture(status_lbl,NULL,NULL,&newpos.w,&newpos.h);
  BaseRenderer::Instance()->RenderTexture(status_lbl,screen,NULL,&newpos);
  location.w=300;
  location.h=newpos.y+newpos.h;

   newpos.y=location.y+4*newpos.h;
   newpos.w=96;
   newpos.h=96;
   /*SDL_Texture *portrait=BaseRenderer::Instance()->LoadImage("Resources/UI/Portraits/Arduin.png");
     BaseRenderer::Instance()->RenderTexture(portrait,screen,NULL,&newpos);*/

  
}

void InspectWindow::Update()
{
	if(target)
	{
	if(target->getGeneralStats()->getHp()!=hp)
	{
		hp=target->getGeneralStats()->getHp();
		string hp_string=std::to_string(target->getGeneralStats()->getHp())+'/'+std::to_string(target->getOriginalStats()->getHp());
		SDL_Surface *hpsurf=TTF_RenderText_Solid(font,hp_string.c_str(),textcolor);
		hp_lbl=SDL_CreateTextureFromSurface( BaseRenderer::Instance()->Renderer(),hpsurf );
		
	}
	}
}


void InspectWindow::setTarget(BaseCharacter *target)
{
	if(target && target!=this->target)
	{
		this->target=target;
		SDL_Surface *namesurf=TTF_RenderText_Solid(font,target->getInfo()->getName().c_str(),textcolor);
		name_lbl=SDL_CreateTextureFromSurface( BaseRenderer::Instance()->Renderer(), namesurf);

		SDL_Surface *classsurf=TTF_RenderText_Solid(font,target->getInfo()->getClass().c_str(),textcolor);
		class_lbl=SDL_CreateTextureFromSurface( BaseRenderer::Instance()->Renderer(), classsurf);
		
		SDL_Surface *racesurf=TTF_RenderText_Solid(font,target->getInfo()->getRace().c_str(),textcolor);
		race_lbl=SDL_CreateTextureFromSurface( BaseRenderer::Instance()->Renderer(), racesurf);
		string hp_string=std::to_string(target->getGeneralStats()->getHp())+'/'+std::to_string(target->getOriginalStats()->getHp());
		SDL_Surface *hpsurf=TTF_RenderText_Solid(font,hp_string.c_str(),textcolor);
		hp_lbl=SDL_CreateTextureFromSurface( BaseRenderer::Instance()->Renderer(),hpsurf );
		
		SDL_Surface *statussurf=TTF_RenderText_Solid(font,"Healthy",textcolor);
		status_lbl=SDL_CreateTextureFromSurface( BaseRenderer::Instance()->Renderer(), statussurf);
		hp=target->getGeneralStats()->getHp();
	}
	
}


SDL_Rect InspectWindow::getRect()
{
	return this->location;
}


void InspectWindow::HandleEvents(SDL_Event *event)
{
	std::cout<<target->getPosition().x<<','<<target->getPosition().y<<endl;
	std::cout<<"Inspecting:"<<event->button.x<<','<<event->button.y<<endl;
	
	pair<int,int> pos=camera->Translate(event->button.x,event->button.y);
	std::cout<<"Translation:"<<pos.first/TILE_SIZE*TILE_SIZE<<','<<pos.second/TILE_SIZE*TILE_SIZE<<endl;
	CellInfo *cell=MapIndex::Instance()->getCell(pos.second/TILE_SIZE,pos.first/TILE_SIZE);
	if(cell!=NULL)
	{
		std::cout<<cell->getID()<<':'<<cell->getType()<<endl;
		if(cell->getType()==CHARACTER_T)
		{
			setTarget(KnowledgePool::Instance()->getCharacter(cell->getID()));
			
		}
	}
}
