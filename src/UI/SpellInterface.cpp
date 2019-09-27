#include "SpellInterface.h"
#include "InputState.h"
#include "UserInputHandler.h"
#include "BaseRenderer.h"
SpellInterface::SpellInterface(TurnEngine *t_e,Caster *caster,Camera *camera):t_e(t_e),caster(caster),camera(camera)
{
	int level=ceil(caster->getGeneralStats()->getLevel()/2.0);
	level_buttons=new ButtonMenu(O_DOWN,SDL_Rect{0,0,0,0});
	level_buttons->Add("Level0","Resources/UI/Icons/C.png");
	level_buttons->Add("Level1","Resources/UI/Icons/I.png");
	if(level>=2)
		level_buttons->Add("Level2","Resources/UI/Icons/II.png");
	if(level>=3)
		level_buttons->Add("Level3","Resources/UI/Icons/III.png");
	if(level>=4)
		level_buttons->Add("Level4","Resources/UI/Icons/IV.png");
	level_buttons->Show(true);
	int width,height;
	SDL_QueryTexture(level_buttons->GetButtons()[0]->GetImage(),NULL,NULL,&width,&height);
	for(int i=0;i<=level;i++)
	{
		spell_buttons[i]=new ButtonMenu(O_RIGHT,SDL_Rect{(short)(width),(short)(height*i),0,0});;
	}
	UpdatePreparedSpells();
}

SpellInterface::SpellInterface(TurnEngine *t_e,Caster *caster,Camera *camera,SDL_Rect starting_pos):t_e(t_e),caster(caster),camera(camera)
{
	level_buttons=new ButtonMenu(O_DOWN,starting_pos);
	int level=ceil(caster->getGeneralStats()->getLevel()/2.0);
	level_buttons->Add("Level0","Resources/UI/Icons/C.png");
	level_buttons->Add("Level1","Resources/UI/Icons/I.png");
	if(level>=2)
		level_buttons->Add("Level2","Resources/UI/Icons/II.png");
	if(level>=3)
		level_buttons->Add("Level3","Resources/UI/Icons/III.png");
	if(level>=4)
		level_buttons->Add("Level4","Resources/UI/Icons/IV.png");
	level_buttons->Show(true);

	int width,height;
	SDL_QueryTexture(level_buttons->GetButtons()[0]->GetImage(),NULL,NULL,&width,&height);
	for(int i=0;i<=level;i++)
	{
		spell_buttons.push_back(new ButtonMenu(O_RIGHT,SDL_Rect{(short)(starting_pos.x+width),(short)(starting_pos.y+height*i),0,0}));
	}
	UpdatePreparedSpells();

}
SpellInterface::~SpellInterface()
{
	delete level_buttons;

	for(int i=0;i<spell_buttons.size();i++)
	{
		delete spell_buttons[i];
	}

}
void SpellInterface::HandleEvents(SDL_Event *event)
{
	if(t_e->GetTurn() && !t_e->GetTurn()->AIControlled())
	{
		if(event->button.button == SDL_BUTTON_LEFT)
		{
			pair<int,int> pos=camera->Translate(event->button.x,event->button.y);
			for(int i=0;i<spell_buttons.size();i++)
			{
				Button *button=spell_buttons[i]->Clicked(pos.first,pos.second);
				if(button)
				{
					if (!t_e->GetTurn()->StandardActionDone())
					{
						cout<<"Casting:"<<button->GetName()<<" From Prepared Spells"<<endl;
						t_e->GetTurn()->GetUserInputHandler()->SetState(new SpellState(t_e->GetTurn(),button->GetName()));
					}
				}
			}
		}
	}
}
void SpellInterface::Draw(SDL_Texture *screen)
{
	//might kill performance seems fast enough for now callback if needed
	if(num_spells>caster->GetNumPreparedSpells())
	{
		UpdatePreparedSpells();
		//if we update clear the screen
	}
	level_buttons->Draw(screen);
	for(int i=0;i<spell_buttons.size();i++)
	{
		spell_buttons[i]->Draw(screen);
	}
}

void SpellInterface::UpdatePreparedSpells()
{
	int level=ceil(caster->getGeneralStats()->getLevel()/2.0);
	for(int i=0;i<=level;i++)
	{
		spell_buttons[i]->Clear();
	}
  
	multiset<Spell*> prepared_spells=caster->GetPreparedSpells();
	num_spells=caster->GetNumPreparedSpells();
	cout<<"Num Spells:"<<num_spells<<" num_prepared:"<<caster->GetNumPreparedSpells()<<endl;
	multiset<Spell*>::iterator mit;
	for(mit=prepared_spells.begin();mit!=prepared_spells.end();++mit)
	{
		Spell *sp=(Spell*)(*mit);
		cout<<sp->GetSpellStats()->GetLevel()<<','<<sp->GetSpellInfo()->getName()<<':'<<sp->GetIcon()<<endl;
		spell_buttons[sp->GetSpellStats()->GetLevel()]->Add(sp->GetSpellInfo()->getName(),sp->GetIcon());
		spell_buttons[sp->GetSpellStats()->GetLevel()]->Show(true);
	}
}
