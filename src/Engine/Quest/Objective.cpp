#include "Objective.h"


Objective::Objective(string name)
{
	this->name=name;
}

Objective::~Objective()
{
}


bool Objective::success()
{
	return true;
}


string Objective::getName()
{
	return this->name;
}

