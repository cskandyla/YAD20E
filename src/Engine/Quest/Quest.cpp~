#include "Quest.h"
#include <string>
using std::string;



Quest::Quest(string name)
{
	this->name=name;
}

Quest::~Quest()
{

	for(int i=0;i<objectives.size();i++)
	{
		delete objectives[i];
	}
}

bool Quest::success()
{
	for(int i=0;i<objectives.size();i++)
	{
		if(!objectives[i]->success())
		{
			return false;
		}
	}
	return true;
}



void Quest::addObjective(Objective *objective)
{
	objectives.push_back(objective);
}


string Quest::status()
{
	
	string status=name;
	if(success())
		name+="[Complete]";
	name+="\n";
	for(int i=0;i<objectives.size();i++)
	{
		name+=objectives[i]->getName();
		if(objectives[i]->success())
		{
			name+="[Complete]";
		}
		name+="\n";
	}
	return status;
}
