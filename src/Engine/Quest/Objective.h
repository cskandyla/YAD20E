#include <string>
using std::string;


#ifndef __OBJECTIVE__H__
#define __OBJECTIVE__H__

class Objective
{

private:
	string name;
	

public:
	Objective(string name);
	~Objective();
	virtual bool success()=0;
	string getName();
};

#endif
