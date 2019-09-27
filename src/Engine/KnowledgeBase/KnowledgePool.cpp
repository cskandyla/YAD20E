#include "KnowledgePool.h"
KnowledgePool* KnowledgePool::k_pool=NULL;

KnowledgePool::KnowledgePool()
{
  
}
KnowledgePool* KnowledgePool::Instance()
{
	if(!k_pool)
		k_pool=new KnowledgePool();
	return k_pool;
}
void KnowledgePool::Init()
{
  
}

void KnowledgePool::Free()
{
	for (std::unordered_map<string,Team*>::iterator it=teams.begin(); it!=teams.end(); ++it)
		delete it->second;
	std::unordered_map<unsigned int,BaseCharacter*>::iterator  c_it;
	for(c_it=characters.begin();c_it!=characters.end();++c_it)
	{
		delete c_it->second;
	}
	cout<<"Deleting KnowledgePool items"<<endl;
	/*segfaults
	  std::unordered_map<unsigned int,Item*>::iterator i_it;
	  for(i_it=items.begin();i_it!=items.end();++i_it)
	  {
	
	  delete i_it->second;
	  }*/
}


void KnowledgePool::AddTeam(Team *team)
{
	teams[team->GetName()]=team;
}

Team* KnowledgePool::GetTeam(string team)
{
	if(teams.find(team)!=teams.end())
	{
		return teams[team];
	}
	return NULL;
}

void KnowledgePool::AddAffiliation(string team1,string team2,TEAM_AFFILIATION affiliation)
{
	if(teams.find(team1)!=teams.end() && teams.find(team2)!=teams.end())
	{
		teams[team1]->AddAffiliation(team2,affiliation);
		teams[team2]->AddAffiliation(team1,affiliation);
	}
}

BaseCharacter* KnowledgePool::getCharacter(unsigned int id)
{
	std::unordered_map<unsigned int,BaseCharacter*>::iterator it;
	it=characters.find(id);
	if(it==characters.end())
	{
		return NULL;
	}

	else
	{
		return it->second;
	}
}
Item* KnowledgePool::getItem(unsigned int id)
{
	std::unordered_map<unsigned int,Item*>::iterator it;
	it=items.find(id);
	if(it==items.end())
	{
		return NULL;
	}

	else
	{
		return it->second;
	}
}
std::unordered_map<unsigned int,BaseCharacter*>& KnowledgePool::getCharacters()
{
	return this->characters;
}
std::unordered_map<unsigned int,Item*>& KnowledgePool::getItems()
{
	return this->items;
}

std::unordered_map<unsigned int,AIEntity*>& KnowledgePool::getAI()
{
	return this->AIEntities;
}


bool KnowledgePool::AddCharacter(BaseCharacter *bchar)
{
	
	cout<<bchar<<endl;
	if(bchar){
		pair<unsigned int,BaseCharacter*> p(characters.size()+1,bchar);
		characters.insert(p);
		bchar->setID(characters.size());
		return true;
	}
	return false;
}
bool KnowledgePool::RemoveCharacter(unsigned int id)
{
	return false;
}
bool KnowledgePool::AddItem(Item *it)
{

	if(it)
	{
		pair<unsigned int,Item*> p(items.size()+1,it);
		items.insert(p);
		it->setID(items.size());
		return true;
	}
	return false;
}
bool KnowledgePool::RemoveItem(unsigned int id)
{
	return false;
}

bool KnowledgePool::AddAIEntity(unsigned int id,AIEntity* ai)
{
	if(characters.find(id)!=characters.end())
	{
		AIEntities[id]=ai;
		return true;
	}
	return false;
}
