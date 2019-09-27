#include "Quests.h"
#include "KnowledgePool.h"
#include "Team.h"
#include "BuiltinObjective.h"
#include "Quest.h"

Objective_Entry BuiltinObjectives[]=
  { {"all_goblins_dead",all_goblins_killed},
    {NULL,NULL}
  };


int LookUpObjective(const char *objective_name)
{
  int i=0;
  while(BuiltinObjectives[i].objective_name!=NULL)
    {
      if(strcmp(BuiltinObjectives[i].objective_name,objective_name)==0)
	{
	  return i;
	}
      i++;
    }
  return -1;
}





bool all_goblins_killed()
{
	set<unsigned int> goblinz=KnowledgePool::Instance()->GetTeam("Goblinz")->GetMembers();
        set<unsigned int>::iterator goblin_it;
	for(goblin_it=goblinz.begin();goblin_it!=goblinz.end();++goblin_it)
	{
		if(KnowledgePool::Instance()->getCharacter(*goblin_it)->getState()!=STATE_DEAD)
		{
			return false;
		}
	}

	return true;
}

