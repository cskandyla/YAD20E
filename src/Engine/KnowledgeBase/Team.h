#include <string>
#include <set>
#include <unordered_map>
using std::string;
using std::set;
using std::unordered_map;

#ifndef __TEAM_H
#define __TEAM_H

enum TEAM_AFFILIATION {TEAM_ALLY=0,TEAM_ENEMY,TEAM_NEUTRAL,TEAM_NONE};
class Team
{
private:
	string name;
	set<unsigned int> members;
	unordered_map<string,TEAM_AFFILIATION> affiliations;
public:
	Team(string name,set<unsigned int> members);
	virtual ~Team();
	string GetName();
  
	void AddMember(unsigned int member);
	bool IsMember(unsigned int mid);
	const set<unsigned int> GetMembers();
  
  
	void AddAffiliation(string team,TEAM_AFFILIATION affiliation);
	TEAM_AFFILIATION GetAffiliation(string team);
};

#endif
