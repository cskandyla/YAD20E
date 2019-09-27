#include "Team.h"


Team::Team(string name,set<unsigned int> members):name(name),members(members)
{

}

Team::~Team()
{
  
}

const set<unsigned int> Team::GetMembers()
{
	return this->members;
}

string Team::GetName()
{
  return this->name;
}
  
void Team::AddMember(unsigned int member)
{
  members.insert(member);
}
bool Team::IsMember(unsigned int mid)
{
  if(members.find(mid)!=members.end())
    return true;
  return false;
}
  
void Team::AddAffiliation(string team,TEAM_AFFILIATION affiliation)
{
  affiliations[team]=affiliation;
}
TEAM_AFFILIATION Team::GetAffiliation(string team)
{
  
  if(affiliations.find(team)!=affiliations.end())
    {
      return affiliations[team];
    }
  return TEAM_NONE;
}
