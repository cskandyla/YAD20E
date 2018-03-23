#include "Colision.h"




Line:: Line(int x0,int y0,int x1,int y1):startp(x0,y0),endp(x1,y1)
{

}
Line:: Line(pair<int,int> startp,pair<int,int> endp):startp(startp),endp(endp)
{

}
void Line::SetStart(pair<int,int> startp)
{
  this->startp=startp;
}
void Line::SetEnd(pair<int,int> endp)
{
  this->endp=endp;
}
pair<int,int> Line::GetStart()
{
  return this->startp;
}
pair<int,int> Line::GetEnd()
{
  return this->endp;
}

bool Colision::PointInRect(pair<int,int> p,SDL_Rect r)
{
  if(p.first>=r.x && p.first<=r.x+r.w && p.second>=r.y && p.second <=r.y+r.h)
    {
      return true;
    }
  return false;

}


bool Colision::LineLine(Line xline,Line yline)
{
  float x1 = xline.GetStart().first, x2 = xline.GetEnd().first;
  float x3 = yline.GetStart().first, x4 = yline.GetEnd().first;
  float y1 = xline.GetStart().second, y2 = xline.GetEnd().second,
    y3 = yline.GetStart().second, y4 = yline.GetEnd().second;
 
float d = (x1 - x2) * (y3 - y4) - (y1 - y2) * (x3 - x4);
// If d is zero, there is no intersection
if (d == 0) return false;
 
// Get the x and y
float pre = (x1*y2 - y1*x2), post = (x3*y4 - y3*x4);
float x = ( pre * (x3 - x4) - (x1 - x2) * post ) / d;
float y = ( pre * (y3 - y4) - (y1 - y2) * post ) / d;
 
// Check if the x and y coordinates are within both lines
 if ( x < std::min(x1, x2) || x > std::max(x1, x2) ||
      x < std::min(x3, x4) || x > std::max(x3, x4) ) return false;
 if ( y < std::min(y1, y2) || y > std::max(y1, y2) ||
      y < std::min(y3, y4) || y > std::max(y3, y4) ) return false;
 
 return true;
}
bool Colision::LineRect(Line line,SDL_Rect rect)
{

  //x1,x2 >= x && <= x+w
  //y,y2 >= y && <= y+h
  //is inside
  if(line.GetStart().first>=rect.x && line.GetStart().first<=rect.x+rect.w  &&  line.GetEnd().first>=rect.x &&  line.GetEnd().first<=rect.x+rect.w &&
     line.GetStart().second>=rect.y && line.GetStart().second<=rect.y+rect.h &&  line.GetEnd().second>=rect.y &&  line.GetEnd().second<=rect.y+rect.y)
    {
      return true;
    }  
  Line rectline1(rect.x,rect.y,rect.x+rect.w,rect.y);
  Line rectline2(rect.x,rect.y,rect.x,rect.y+rect.h);
  Line rectline3(rect.x+rect.w,rect.y,rect.x+rect.w,rect.y+rect.h);
  Line rectline4(rect.x,rect.y+rect.h,rect.x+rect.w,rect.y+rect.h);
  if(LineLine(line,rectline1) || LineLine(line,rectline2) || LineLine(line,rectline3) || LineLine(line,rectline4))
    {
      return true;
    }
  
  
  return false;
}
bool Colision::RectRect(SDL_Rect big,SDL_Rect small)
{

  if(small.x>big.x+big.w)
    return false;
  else if(small.y+small.h<big.y)
    return false;
  else if(small.x+small.w<big.x)
    return false;
  if(small.y>big.y+big.h)
    return false;
  return true;
}

