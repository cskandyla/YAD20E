#include <string>
using std::string;

#ifndef __TRIGGER__
#define __TRIGGER__
class Trigger
{
private:
    int x,y;
    string script;
public:
    Trigger(int x,int y,string script);
    int getX()
    {
        return x;
    }
    int getY()
    {
        return y;
    }
    string& getScript()
    {
        return script;
    }

};
#endif
