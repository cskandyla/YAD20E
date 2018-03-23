#include "Turn.h"
#include <iostream>
#include "Zombie.h"
#include "Seeker.h"
#include "params.h"
#include "UserInputHandler.h"
#include "Caster.h"
#include "KnowledgePool.h"
Turn::Turn(BaseCharacter *bchar,Camera *camera,AIEntity *ent)
{

  cur_char=bchar;
  this->moves=bchar->getGeneralStats()->getSpeed();
  this->camera=camera;
  this->Done=false;
  SetMoved(false);
  SetStandardAction(false);
  this->ent=ent;
  if(ent!=NULL)
    {
      ent->Reset();
      user_handler=NULL;
    }
  else
    {
      user_handler=new UserInputHandler(this->camera,this);
    }
  cout<<"current character: "<<cur_char->getID()<<"AIEntity: "<<ent<<endl;
  cur_char->OnTurnStart();
  std::unordered_map<unsigned int,BaseCharacter*>::iterator it= KnowledgePool::Instance()->getCharacters().begin();
  for(it= KnowledgePool::Instance()->getCharacters().begin(); it!= KnowledgePool::Instance()->getCharacters().end(); it++)
    {
      it->second->SetReactionDone(true);
    }
}

Turn::~Turn()
{
  if(user_handler)
    delete user_handler;
}

bool Turn::HasMoved()
{
  return this->cur_char->Moved();
}
bool Turn::StandardActionDone()
{
  return this->cur_char->ActionDone();
}
bool Turn::TurnDone()
{
  return Done;
}
void Turn::SetMoved(bool Moved)
{
  this->cur_char->SetMoved(Moved);
}
void Turn::SetStandardAction(bool standard_action)
{
  this->cur_char->SetActionDone(standard_action);
    
}

bool Turn::ReactionsDone()
{
  std::unordered_map<unsigned int,BaseCharacter*>::iterator it= KnowledgePool::Instance()->getCharacters().begin();
  for(it= KnowledgePool::Instance()->getCharacters().begin(); it!= KnowledgePool::Instance()->getCharacters().end(); it++)
    {
      if(!it->second->ReactionDone())
	return false;
    }
  return true;
}

bool Turn::Turn_Done()
{
  return Done;
}

void Turn::SetDone(bool Done)
{
  this->Done=Done;
}

BaseCharacter* Turn::TheCharacter()
{
  return this->cur_char;
}
void Turn::Update(float time)
{
  std::unordered_map<unsigned int,BaseCharacter*>::iterator it= KnowledgePool::Instance()->getCharacters().begin();
  for(it= KnowledgePool::Instance()->getCharacters().begin(); it!= KnowledgePool::Instance()->getCharacters().end(); it++)
    {
      it->second->Update(time);
    }
  if(ent==NULL)
    {  
      if(cur_char->Moved() && !TheCharacter()->Active())
	{
	  //MapIndex::Instance()->CharIndexUpdate(TheCharacter(),0,0);
	  // MapIndex::Instance()->ComputeVision(TheCharacter()->getPosition());
	}
    }
  else
    {	
      if(ent->TurnDone() /*&& ReactionsDone()*/)
	{
	  Done = true;
	}
      else if(ent->ActionFinished())
	{
	  //MapIndex::Instance()->CharIndexUpdate(TheCharacter(),0,0);
	  ent->Update();
	}  
    }
  
  if(cur_char->Moved() && cur_char->ActionDone()  && !TheCharacter()->Active() /* && ReactionsDone()*/)
    {
      Done=true;
    }
}

void Turn::Handle_Events(SDL_Event *event)
{
  
 
  if(ent==NULL)
    {
      user_handler->HandleEvents(event);
    }
}

Camera* Turn::GetCamera()
{
  return this->camera;
}

UserInputHandler* Turn::GetUserInputHandler()
{
  return this->user_handler;
}

bool Turn::AIControlled()
{
  if(ent!=NULL)
    return true;
  return false;
}
