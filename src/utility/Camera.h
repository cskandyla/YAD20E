#include <SDL2/SDL.h>
#include <utility>
using std::pair;
#ifndef __CAMERA_H_
#define __CAMERA_H_
class CellInfo;
class Camera
{
 private:
  SDL_Rect *cam;
  pair<int,int> pos;
 public:
  //
  Camera(SDL_Rect *cam_surf,pair<int,int> pos);
  virtual ~Camera();
  //
  pair<int,int> Translate(int xpos,int ypos);
  CellInfo *ClickedCell(int xpos,int ypos);
  SDL_Rect ClickedRect(int xpos,int ypos);
  pair<int,int> RectToPair(SDL_Rect r);

  //
  pair<int,int> Get();
  void Set(int x,int y);
  SDL_Rect* GetCam();
  
};


#endif
