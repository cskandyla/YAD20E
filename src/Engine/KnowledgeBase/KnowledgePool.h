#include "Team.h"
#include <unordered_map>
#include <string>
#include "BasicCharacter.h"
#include "Item.h"
#include "AIEntity.h"
using std::unordered_map;
using std::string;
//#include "Quest.h"
#ifndef __KNOWLEDGE_POOL
#define __KNOWLEDGE_POOL

//Singleton since it's probably gonna get overused
class KnowledgePool
{
 private:
  static KnowledgePool* k_pool;
  KnowledgePool();

  //Our Persistent Game Enitites
  unordered_map <string,Team*> teams;
  std::unordered_map<unsigned int,BaseCharacter*> characters;
  std::unordered_map<unsigned int,Item*> items;
  std::unordered_map<unsigned int,AIEntity*> AIEntities;

 public:
  static KnowledgePool* Instance();
  void Init();
  void Free();

  //Team
  void AddTeam(Team* team);
  void AddAffiliation(string team1,string team2,TEAM_AFFILIATION affiliation);
  Team* GetTeam(string team);

  //Getters
  BaseCharacter* getCharacter(unsigned int id);
  Item* getItem(unsigned int id);
  std::unordered_map<unsigned int,BaseCharacter*>& getCharacters();
  std::unordered_map<unsigned int,Item*>& getItems();
  std::unordered_map<unsigned int,AIEntity*>& getAI();

  //Add/Remove
  bool AddAIEntity(unsigned int id,AIEntity* ai);
  bool AddCharacter(BaseCharacter *bchar);
  bool RemoveCharacter(unsigned int id);
  bool AddItem(Item *it);
  bool RemoveItem(unsigned int id);
  
};
#endif
