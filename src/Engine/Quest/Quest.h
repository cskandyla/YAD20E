#include "Objective.h"
#include <vector>
using std::vector;

#ifndef __QUEST__H__
#define __QUEST__H__

class Quest
{
	
private:
	string name;
	vector<Objective*> objectives;

public:
	Quest(string name);
	~Quest();
	void addObjective(Objective *objective);
	bool success();
	string status();
	string getName();
};


#endif
