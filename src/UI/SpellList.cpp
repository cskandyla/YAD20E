#include "SpellList.h"
#include "BaseRenderer.h"
#include "params.h"
#include <set>
#include <iostream>
#include <algorithm>
using std::cout;
using std::endl;
using std::set;
using std::multiset;
#define BUTTON_SIZE 32
#define MAX_PREPARED 5
//pass relevant spell table for the class?
SpellList::SpellList(TTF_Font *font,Caster *caster):caster(caster)
{
  shown=false;
  SDL_Color textcolor;
  textcolor.r=80;
  textcolor.g=0;
  textcolor.b=0;
  int level=ceil(caster->getGeneralStats()->getLevel()/2.0);
  cout<<"Level"<<level<<endl;
  SDL_Surface *prepsurf=TTF_RenderText_Solid(font,"Prepared:",textcolor);
  int prep_w=prepsurf->w,prep_h=prepsurf->h;
  
  Preparedlbl=SDL_CreateTextureFromSurface( BaseRenderer::Instance()->Renderer(), prepsurf);
  SDL_FreeSurface(prepsurf);
  SDL_Surface *lblsufr=TTF_RenderText_Solid(font,"Known:",textcolor);
  int know_w=lblsufr->w,know_h=lblsufr->h;
  Knownlbl= SDL_CreateTextureFromSurface( BaseRenderer::Instance()->Renderer(), lblsufr);
  SDL_FreeSurface(lblsufr);
  for(int i=0;i<=level;i++)
    {
      char label_txt[20];
      sprintf(label_txt,"Level%d:\0",i);
      SDL_Surface *label=TTF_RenderText_Solid(font,label_txt,textcolor);
      int label_w=label->w,label_h=label->h;
      
      SDL_Texture *labelTexture = SDL_CreateTextureFromSurface( BaseRenderer::Instance()->Renderer(), label );
      SDL_FreeSurface( label);
      Labels.push_back(labelTexture);
      ButtonMenu *Pbmenu=new ButtonMenu(O_RIGHT,SDL_Rect{(short)(prep_w),(short)(prep_h+i*BUTTON_SIZE),BUTTON_SIZE,BUTTON_SIZE});
      Pbmenu->SetBackground("Resources/UI/Buttons/frame1.png");
      Prepared.push_back(Pbmenu);

      ButtonMenu *Abmenu=new ButtonMenu(O_RIGHT,SDL_Rect{(short)(BUTTON_SIZE*6+label_w/2+know_w),(short)(know_h+i*BUTTON_SIZE),BUTTON_SIZE,BUTTON_SIZE});
      Abmenu->SetBackground("Resources/UI/Buttons/frame0.png");
      All.push_back(Abmenu);
      
    }
  if(caster)
    {
      cout<<"Caster:"<<caster<<endl;
      set<Spell*>::iterator it;
      set<Spell*> all_spells=caster->GetKnownSpells();
   
      for(it=all_spells.begin();it!=all_spells.end();++it)
	{
	  cout<<(*it)->GetSpellStats()->GetLevel()<<','<<(*it)->GetSpellInfo()->getName()<<':'<<(*it)->GetIcon()<<endl;
	  All[(*it)->GetSpellStats()->GetLevel()]->Add((*it)->GetSpellInfo()->getName(),(*it)->GetIcon());
	}
      multiset<Spell*> prepared_spells=caster->GetPreparedSpells();
      multiset<Spell*>::iterator mit;
      for(mit=prepared_spells.begin();mit!=prepared_spells.end();++mit)
	{
	  Spell *sp=(Spell*)(*mit);
	  cout<<sp->GetSpellStats()->GetLevel()<<','<<sp->GetSpellInfo()->getName()<<':'<<sp->GetIcon()<<endl;
	  Prepared[sp->GetSpellStats()->GetLevel()]->Add(sp->GetSpellInfo()->getName(),sp->GetIcon());
	}
    }

  for(int i=0;i<All.size();i++)
    {
      if(All[i]->size()>0)
	{
	  All[i]->Show(true);
	}
      if(Prepared[i]->size()>0)
	{
	  Prepared[i]->Show(true);
	}
    }
}

SpellList::~SpellList()
{
  SDL_DestroyTexture(Preparedlbl);
  SDL_DestroyTexture(Knownlbl);
  for(int i=0;i<Labels.size();i++)
    {
      SDL_DestroyTexture(Labels[i]);
    }

  for(int i=0;i<All.size();i++)
    {
      delete All[i];
      delete Prepared[i];
    }


}


bool SpellList::Prepare(Button *button,int level)
{
  if(button)
    {
      if(Prepared[level]->size()<caster->getNumSlots(level))
	{
	  if(caster->Prepare(button->GetName()))
	    Prepared[level]->Add(button->GetName(),button->GetImage());
	  return true;
	}

    }
  return false;
}

bool SpellList::Forget(Button *button,int level)
{
  if(button)
    {
      Prepared[level]->Remove(button);
      caster->Forget(button->GetName());
      return true;
    }

  return false;
}

//Clear
void SpellList::ClearAll()
{

}
void SpellList::ClearMenu(int level)
{

}

void SpellList::HandleEvents(SDL_Event *event)
{

  switch (event->type)
    {
    case SDL_MOUSEBUTTONDOWN :
      {

	  
	if(event->button.button == SDL_BUTTON_LEFT)
	  {
	    int xpos=event->button.x;
	    int ypos=event->button.y;
	    for(int i=0;i<Prepared.size();i++)
	      {
		Button *button=Prepared[i]->Clicked(xpos,ypos);
		if(button)
		  {
		    //Handle Removing Prepared
		    cout<<"Removing:"<<button->GetName()<<" From Prepared Spells"<<endl;
		    Forget(button,i);
		  }
	      }
	    for(int i=0;i<All.size();i++)
	      {
		Button *button=All[i]->Clicked(xpos,ypos);
		if(button)
		  {
		    //Handle Removing Prepared
		    cout<<"Adding:"<<button->GetName()<<" To Prepared Spells"<<endl;
		    Prepare(button,i);
		  }
	      }
	  }
      }
      break; 
    }

}
void SpellList::Draw(SDL_Texture *screen)
{
  //BaseRenderer::Instance()->Renderer
  //SDL_RenderClear(BaseRenderer::Instance()->Renderer());
  int prep_w,prep_h;
  SDL_QueryTexture(Preparedlbl,NULL,NULL,&prep_w,&prep_h);
  SDL_Rect newpos;
  newpos.x=0;
  newpos.y=0;
  newpos.w=prep_w;
  newpos.h=prep_h;
  // SDL_BlitSurface(Preparedlbl,NULL,screen,&newpos);
  BaseRenderer::Instance()->RenderTexture(Preparedlbl,screen,NULL,&newpos);
  int lbl0_w,lbl0_h;
  SDL_QueryTexture(Labels[0],NULL,NULL,&lbl0_w,&lbl0_h);
  newpos.x=BUTTON_SIZE*6+lbl0_w/2;
  //  SDL_BlitSurface(Knownlbl,NULL,screen,&newpos);
  BaseRenderer::Instance()->RenderTexture(Knownlbl,screen,NULL,&newpos);
  int lbl_w,lbl_h;
  for(int i=0;i<Labels.size();i++)
    {
      
      SDL_QueryTexture(Labels[i],NULL,NULL,&lbl_w,&lbl_h);
      SDL_Rect newpos;
      newpos.x=prep_w-lbl_w;
      newpos.y=prep_h+i*BUTTON_SIZE;
      newpos.w=lbl_w;
      newpos.h=lbl_h;
      BaseRenderer::Instance()->RenderTexture(Labels[i],screen,NULL,&newpos);
	//      SDL_BlitSurface(Labels[i],NULL,screen,&newpos);
    }

  for(int i=0;i<Prepared.size();i++)
    {
      Prepared[i]->Draw(screen);
    }
  //    cout<<"All"<<endl;

  for(int i=0;i<All.size();i++)
    {
      All[i]->Draw(screen);
    }
}

void SpellList::Show(bool shown)
{
  this->shown=shown;
}

bool SpellList::Shown()
{
  return shown;
}


vector<ButtonMenu*>& SpellList::GetPrepared()
{
  return Prepared;
}
