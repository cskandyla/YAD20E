#ifndef __QUEST_FUNCS__
#define __QUEST_FUNCS__


typedef bool (*success_func)();

struct Objective_Entry
{
  const char* objective_name;
  success_func objective_func;
  
};

extern Objective_Entry BuiltinObjectives[];

int LookUpObjective(const char *objective_name);

void DemoKillGoblins();
bool all_goblins_killed();
bool always_succeed();
#endif
