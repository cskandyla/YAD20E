#include "BuiltinObjective.h"

BuiltinObjective::BuiltinObjective(string name,bool (*success_func)()):Objective(name)
{
	this->success_func=success_func;
}


bool BuiltinObjective::success()
{
	return success_func();
}
