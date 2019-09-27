#include "Objective.h"


#ifndef BUILTIN_OBJECTIVE_H
#define BUILTIN_OBJECTIVE_H

class BuiltinObjective: public Objective
{
private:
	bool (*success_func)();
public:
	
	BuiltinObjective(string name,bool (*success_func)());
	virtual bool success();
};

#endif
