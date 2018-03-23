#include <SDL2/SDL.h>
#include <utility>
#include <algorithm>
using std::pair;

class Line
{
 private:
  pair<int,int> startp;
  pair<int,int> endp;
 public:
  Line(int x0,int y0,int x1,int y1);
  Line(pair<int,int> startp,pair<int,int> endp);
  void SetStart(pair<int,int> startp);
  void SetEnd(pair<int,int> endp);
  pair<int,int> GetStart();
  pair<int,int> GetEnd();
  
};

class Colision
{
 public:
  static bool PointInRect(pair<int,int> p,SDL_Rect r);
  static bool LineLine(Line x,Line y);
  static bool LineRect(Line line,SDL_Rect rect);
  static bool RectRect(SDL_Rect big,SDL_Rect small);

};
