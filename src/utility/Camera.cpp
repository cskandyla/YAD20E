#include "Camera.h"
#include "MapIndex.h"
#include "params.h"

Camera::Camera(SDL_Rect *cam,pair<int,int> pos):cam(cam),pos(pos)
{
}

pair<int,int> Camera::Translate(int xpos,int ypos)
{
  return pair<int,int>(pos.first+xpos-cam->x,pos.second+ypos-cam->y);
}

Camera::~Camera()
{

}


CellInfo* Camera::ClickedCell(int xpos,int ypos)
{
  SDL_Rect cell_rect;
  cell_rect.x=(pos.first+xpos-cam->x)/TILE_SIZE*TILE_SIZE;
  cell_rect.y=(pos.second+ypos-cam->y)/TILE_SIZE*TILE_SIZE;
  cell_rect.w=TILE_SIZE;
  cell_rect.h=TILE_SIZE;
  CellInfo *cellinfo= MapIndex::Instance()->getCell((cell_rect.y)/TILE_SIZE,(cell_rect.x)/TILE_SIZE);
  return cellinfo;
}

SDL_Rect Camera::ClickedRect(int xpos,int ypos)
{
  SDL_Rect cell_rect;
  cell_rect.x=(pos.first+xpos-cam->x)/TILE_SIZE*TILE_SIZE;
  cell_rect.y=(pos.second+ypos-cam->y)/TILE_SIZE*TILE_SIZE;
  cell_rect.w=TILE_SIZE;
  cell_rect.h=TILE_SIZE;
  return cell_rect;
}

pair<int,int> Camera::RectToPair(SDL_Rect r)
{
  return pair<int,int>(r.x/TILE_SIZE,r.y/TILE_SIZE);
}

void Camera::Set(int x,int y)
{
  pos.first=x;
  pos.second=y;
}

pair<int,int> Camera::Get()
{
  return pos;
}

SDL_Rect* Camera::GetCam()
{
  return this->cam;
}

