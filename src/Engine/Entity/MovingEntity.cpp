#include "MovingEntity.h"

#include <cmath>
#include <iostream>
using std::cout;
using std::endl;

MovingEntity::MovingEntity(SDL_Texture *t,int w,int h):Entity(t,w,h),dest(NULL),velx(0.2),vely(0.2)
{
  dir.x=0;
  dir.y=0;
}

MovingEntity::MovingEntity(const MovingEntity &anentity):Entity(anentity)
{
  cout<<"COPYING"<<endl;
  if(anentity.dest!=NULL)
    {
      dest=new Point2d();
      dest->x=anentity.dest->x;
      dest->y=anentity.dest->y;
    }
  else
    {
      dest=NULL;
    }
  position.x=anentity.position.x;
  position.y=anentity.position.y;
  dir.x=anentity.dir.x;
  dir.y=anentity.dir.y;
  velx=anentity.velx;
  vely=anentity.vely;
}

MovingEntity::~MovingEntity()
{
  delete dest;
}

void MovingEntity::SetDestination(Point2d *p)
{
    dest=p;
}


void MovingEntity::SetVelocity(float vx,float vy)
{
    velx=vx;
    vely=vy;

}


void MovingEntity::Update(float time)
{
    if(dest!=NULL)
    {

        dir.x=dest->x-position.x;
        dir.y=dest->y-position.y;

        float length=sqrt(dir.x*dir.x+dir.y*dir.y);
        if(length!=0)
        {
            dir.x/=length;
            dir.y/=length;
            //cout<<"direction vector:"<<dir.x<<','<<dir.y<<"\n";
            position.x+=(dir.x*velx/time);
            position.y+=(dir.y*vely/time);
        }

    }
}

void MovingEntity::setPosition(int x,int y)
{
  SetDestination(x,y);
  Entity::setPosition(x,y);
}

void MovingEntity::SetDestination(int x,int y)
{

    if(dest!=NULL)
    {
        delete dest;
    }
    dest=new Point2d();
    dest->x=x;
    dest->y=y;

}

bool MovingEntity::reachedDestination()
{
    if(dest!=NULL)
      {
	if(position.x==dest->x && position.y==dest->y)	  
            return true;
        else
	  return false;
      }
    return true;
}
