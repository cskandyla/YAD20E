#include "LuaObjective.h"
#include <iostream>
using std::cout;
using std::endl;



LuaObjective::LuaObjective(string name,string lua_func, lua_State *l):Objective(name),lua_func(lua_func),l(l)
{
	
}

bool LuaObjective::magic()
{
}


bool LuaObjective::success()
{

	bool success=false;
	lua_getglobal(l, lua_func.c_str());  /* function to be called */
	cout<<"Attempting to call:"<<lua_func<<endl;
      if (lua_pcall(l, 0, 1, 0) == 0)
      {
    
      /* retrieve result */
	      if (lua_isboolean(l, -1))
	      {
		      success = lua_toboolean(l, -1);
		      lua_pop(l, 1);  /* pop returned value */

	      
	      }
	      else
	      {
		      cout<<"Top of the stack is not a boolean"<<endl;
	      }
      }
      else
      {
	      cout<<"Failed to call"<<lua_func<<endl;
      }
      return success;
}

