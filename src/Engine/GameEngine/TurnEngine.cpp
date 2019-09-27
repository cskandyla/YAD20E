#include "TurnEngine.h"
#include "KnowledgePool.h"
#include <algorithm>
TurnEngine::TurnEngine(Camera *camera, Quest *the_quest):camera(camera),the_quest(the_quest)
{
  it= KnowledgePool::Instance()->getCharacters().begin();
  for(it; it!=KnowledgePool::Instance()->getCharacters().end(); ++it)
    {
	    cout<<"Turn:"<<it->second->getInfo()->getName()<<':'<<it->second->getID()<<endl;
      turn_order.push_back(it->second->getID());
    }
  known_chars=turn_order.size();
  quest_done=false;
  the_turn=NextTurn();
 
}


void TurnEngine::AddTurn(unsigned int character_id)
{
	turn_order.push_back(character_id);
}

TurnEngine::~TurnEngine()
{
  if(the_turn)
    delete the_turn;
}
void TurnEngine::Update(float time)
{
	if(quest_done)
		return;
	
  if(the_turn!=NULL)
    {
      the_turn->Update(time);
      if(the_turn->Turn_Done() && turn_order.size() >=0)
	{
	  delete the_turn;
	  the_turn=NextTurn();
	  if(!the_turn)
	    return;
	}
    }
}


void TurnEngine::Handle_Events(SDL_Event *event)
{
  //TURN ENGINE SPECIFIC EVENTS OR CHARACTER EVENTS NOT IN THE TURN CLASS
  if(the_turn)
    the_turn->Handle_Events(event);


}

Turn* TurnEngine::GetTurn()
{
  return this->the_turn;
}

Turn* TurnEngine::NextTurn()
{
	if(the_quest->success())
	{
		cout<<"QUEUE CREDITS"<<endl;
		quest_done=true;
		return NULL;
	}
	
	cout<<"I know about "<<known_chars<<"characters the knowledge base knows:"<<KnowledgePool::Instance()->getCharacters().size()<<endl;
	if(known_chars<KnowledgePool::Instance()->getCharacters().size())
	{
		//A character has been added, loop through the characters and add any that
		// are not dead and have been added
		std::unordered_map<unsigned int,BaseCharacter*>::iterator chars=
			KnowledgePool::Instance()->getCharacters().begin();
		for(chars ;chars!=KnowledgePool::Instance()->getCharacters().end(); ++chars)
		{

			
			BaseCharacter *achar=chars->second;
			cout<<"Checking for:"<<achar->getID()<<endl;
			if(achar->getGeneralStats()->getHp()>0)
			{
				
				if(std::find(turn_order.begin(),turn_order.end(),achar->getID())==turn_order.end())
				{
					cout<<"Adding:"<<achar->getID()<<endl;
					turn_order.push_back(achar->getID());
					known_chars++;
				}
				
			}
		}
	}
	
  //GET NEW CHARACTER AND HIS CAMERA;
  Turn *new_turn=NULL;
  if(turn_order.size()>0)
  {    cout<<"Front of queue:"<<turn_order.front()<<endl;
      std::unordered_map<unsigned int,AIEntity*>::iterator ait=KnowledgePool::Instance()->getAI().begin();


      //Run through the turn_order and 
      while(KnowledgePool::Instance()->getCharacter(turn_order.front())->getGeneralStats()->getHp()<=0)
	{    
	      cout<<"removing"<<turn_order.front()<<endl;
	      MapIndex::Instance()->getMap()->Set(KnowledgePool::Instance()->getCharacter(turn_order.front())->GetBaseEntity()->getPosition().x/MapIndex::Instance()->getMap()->getTileSize(),
						  KnowledgePool::Instance()->getCharacter(turn_order.front())->GetBaseEntity()->getPosition().y/MapIndex::Instance()->getMap()->getTileSize(),
						  0,LCOLISION);
	      turn_order.pop_front();
	  
	}
      if(turn_order.size()<1)
	return NULL;


      //Check if an AI exists for the character in the order
      if(KnowledgePool::Instance()->getAI().find(turn_order.front())!=KnowledgePool::Instance()->getAI().end())
	{
	  new_turn=new Turn( KnowledgePool::Instance()->getCharacter(turn_order.front()),camera,KnowledgePool::Instance()->getAI().find(turn_order.front())->second);
	}
      else
	{
	  //No-AI
	  new_turn=new Turn( KnowledgePool::Instance()->getCharacter(turn_order.front()),camera,NULL);
	  MapIndex::Instance()->ComputeVision(KnowledgePool::Instance()->getCharacter(turn_order.front())->getPosition());
	}
      
      turn_order.push_back(turn_order.front());
      turn_order.pop_front();
    }
  
  return new_turn;
}


Camera* TurnEngine::GetCamera()
{
  return this->camera;
}
