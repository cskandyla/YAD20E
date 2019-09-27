#include "CharacterDialog.h"
#include "BaseRenderer.h"
#include <iostream>
using std::cout;
using std::endl;

CharacterDialog::CharacterDialog(SDL_Texture *left_portrait, SDL_Texture *right_portrait,SDL_Rect pos,TTF_Font *font):left_portrait(left_portrait),right_portrait(right_portrait),pos(pos)
{
	dialog=SDL_CreateTexture(BaseRenderer::Instance()->Renderer(), SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, pos.w,pos.h);
	SDL_SetTextureBlendMode( dialog, SDL_BLENDMODE_BLEND);
	SDL_SetTextureAlphaMod( dialog, 255 );
	SDL_Rect target;
	target.x=0;
	target.y=0;
	target.w=pos.w/4;
	target.h=pos.h*3/4;


	SDL_SetTextureBlendMode( left_portrait, SDL_BLENDMODE_BLEND);
	SDL_SetTextureAlphaMod( left_portrait, 255 );
	
	BaseRenderer::Instance()->RenderTexture(left_portrait,dialog,NULL,&target);
	target.x=pos.w*3/4;
	target.y=0;
	target.w=pos.w/4;
	target.h=pos.h*3/4;
	BaseRenderer::Instance()->RenderTexture(right_portrait,dialog,NULL,&target);

	text_area=new InfoSurface(pos.w/2,pos.h*3/4,20,20,20,255,font);	
	text_area->AddText("Arduin:",180,20,0);
	text_area->AddText("A modicum of assistance",192,192,192);
	text_area->AddText("would be much appreciated!",192,192,192);
	text_area->AddText("Ase:",20,20,180);
	text_area->AddText("K grapmps ",192,192,192);
	text_area->AddText("Comming up!",192,192,196);
	text_area->AddText("Olaf:",0,180,0);
	text_area->AddText("Not a chance !",192,192,192);
	text_area->AddText("I need all me warriors here",192,192,192);
	text_area->AddText("Bismark:",180,180,20);
	text_area->AddText("Olaf play nice now!",192,192,192);
	
	
	start=0;
	end=text_area->getMaxSize();
	cout<<"Max Size looks to be:"<<text_area->getMaxSize()<<endl;
	text_area->ShowAt(dialog,pos.w/4,0,start,end);
	
	buttons=new ButtonMenu(O_RIGHT,SDL_Rect{pos.w*3/4,pos.h*3/4,0,pos.h*1/4});
	buttons->Add("Down","Resources/UI/Buttons/down_small.png");
	buttons->Add("Up","Resources/UI/Buttons/up_small.png");
	buttons->Add("Close","Resources/UI/Buttons/x_small.png");
	buttons->Show(true);
	buttons->Draw(dialog);
  
       
}

CharacterDialog::CharacterDialog(SDL_Texture *left_portrait, SDL_Texture *right_portrait,SDL_Rect pos,InfoSurface *text_area)
	:left_portrait(left_portrait),right_portrait(right_portrait),pos(pos),text_area(text_area)
{

	dialog=SDL_CreateTexture(BaseRenderer::Instance()->Renderer(), SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, pos.w,pos.h);
	SDL_Rect target;
	target.x=0;
	target.y=0;
	target.w=pos.w/4;
	target.h=pos.h*3/4;
	
	BaseRenderer::Instance()->RenderTexture(left_portrait,dialog,NULL,&target);
	target.x=pos.w*3/4;
	target.y=0;
	target.w=pos.w/4;
	target.h=pos.h*3/4;
	BaseRenderer::Instance()->RenderTexture(right_portrait,dialog,NULL,&target);
	start=0;
	end=text_area->getMaxSize();

	text_area->ShowAt(dialog,pos.w/4,0);
}


void CharacterDialog::Draw(SDL_Texture *screen)
{
	BaseRenderer::Instance()->RenderTexture(dialog,screen,NULL,&pos);
}


void CharacterDialog::HandleEvents(SDL_Event *event)
{
	switch (event->type)
	{

	case SDL_KEYDOWN:
	{
		if (event->key.keysym.sym == SDLK_UP)
		{
			ScrollUp();
			text_area->ShowAt(dialog,pos.w/4,0,start,end);
		}
		else if (event->key.keysym.sym == SDLK_DOWN)
		{
			ScrollDown();
			text_area->ShowAt(dialog,pos.w/4,0,start,end);
		}
	}
	break;
			
		
	case SDL_MOUSEBUTTONDOWN :
	{
		//pair<int,int> loc=camera->Translate(event->button.x,event->button.y);
		pair<int,int> loc(event->button.x,event->button.y);
		cout<<"loc.x"<<loc.first<<" loc.y"<<loc.second<<endl;
		cout<<"pos.x"<<pos.x<<" pos.y"<<pos.y<<endl;

		
		
		
		if(event->button.button == SDL_BUTTON_LEFT)
		{
		      
			Button *button=buttons->Clicked(loc.first,loc.second);
		      
		      
			if(button)
			{
				if(button->GetName()=="Close")
				{
				}
				else if(button->GetName()=="Up")
				{
					ScrollUp();
				}
				else if(button->GetName()=="Down")
				{
					ScrollDown();
				}
				
			}
		}
		
	}
	break;
	}
}


void CharacterDialog::ScrollUp()
{
	if(start>0)
	{
		start--;
		end--;
	}
}
void CharacterDialog::ScrollDown()
{
	if(end<text_area->getSize())
	{
		start++;
		end++;
	}
	
}
