#include "Projectile.h"
#include "BasicCharacter.h"
#include "Colision.h"


#include <iostream>
#include <cmath>
#define M_PI 3.14159265358979323846
Projectile::Projectile(AnimatedEntity* animentity, SDL_Rect target,int velocity)
{
    this->animentity=animentity;

    this->velocity=velocity;
    directionx=0;
    directiony=0;
    this->HasHitTarget=false;
    this->Active=false;
    animentity->setAnimLoop(NO);
    theta=0;
    this->target=target;
    SetUp();
}

Projectile::Projectile(const Projectile &aprojectile)
{
  this->animentity=new AnimatedEntity(*aprojectile.animentity);
  this->target=aprojectile.target;
  this->HasHitTarget=aprojectile.HasHitTarget;
  this->Active=aprojectile.Active;
  this->velocity=aprojectile.velocity;
  this->directionx=aprojectile.directionx;
  this->directiony=aprojectile.directiony;
  this->theta=aprojectile.theta;
}

Projectile::~Projectile()
{
  //Ammo/Spell Should hold the entity
  //delete animentity;
}

void Projectile::UpdateEllipse(float time)
{

  theta+=.1;
  if(theta>=30)
    theta=0.1;
    if(Active)
    {
            float newx,newy;
      newx=150+1*50*cos(theta);
	    newy=150+1*20*sin(theta);
            animentity->setPosition(newx,newy);
	    //cout<<"Elipse Coords:"<<newx<<','<<newy<<endl;
    }

}








void Projectile::Update(float time)
{

    if(Active && !HasHitTarget)
    {
        
        float ndirectionx=target.x-animentity->getPosition().x;
        float ndirectiony=target.y-target.h/2-animentity->getPosition().y+animentity->getPosition().h/2;
        float length=sqrt(ndirectionx*ndirectionx+ndirectiony*ndirectiony);

        ndirectionx=ndirectionx/length;
        ndirectiony=ndirectiony/length;

        if(  ((ndirectionx<=0 && directionx<=0) || (ndirectionx>=0 && directionx>=0) ) && ((ndirectiony<=0 && directiony<=0) || (ndirectiony>=0 && directiony>=0)))
        {
            float newx,newy;
            directionx=ndirectionx;
            directiony=ndirectiony;
            newx=animentity->getPosition().x+velocity*directionx;
            newy=animentity->getPosition().y+velocity*directiony;
            animentity->setPosition(newx,newy);
        }
        else
	  {
            this->HasHitTarget=true;
	    //cout<<"Hit Target"<<endl;
	    
	  }
	animentity->Update(time);
    }

}

void Projectile::Draw(SDL_Texture *screen)
{

    if(!this->HasHitTarget)
        this->animentity->Draw(screen);

}


bool Projectile::Hit()
{
    return HasHitTarget;
}


bool Projectile::IsActive()
{
    return Active;
}


void Projectile::MakeActive(bool active)
{
    this->Active=active;
}


void Projectile::SetPosition(int x, int y)
{

    this->animentity->setPosition(x,y);

}


SDL_Rect Projectile::getPosition()
{

    return animentity->getPosition();
}


void Projectile::SetUp()
{

    Point2d a,b,c;
    a.x=animentity->getPosition().x;
    a.y=animentity->getPosition().y;
    b.x=target.x;
    b.y=target.y;
    float theta=atan2((float)(b.x-a.x),(float)(b.y-a.y));
      float degrees=theta*(180.0/M_PI);
      degrees-=90;
      	if(degrees<0)
	  degrees+=360.0;
	//	 std::cout<<"Final Degrees Calculation:"<<degrees<<endl;

        int numtojump=360/this->animentity->getNumAnims();
        //std::cout<<"Anim to use"<<degrees/numtojump<<endl;

        int ani=((float)degrees/numtojump);
	
	if((int)degrees%numtojump>numtojump/2)
	  ani++;
	if(ani>=animentity->getNumAnims())
	  ani=0;
        animentity->setAnimation(ani);


	
    
}


void Projectile::Reset()
{

    directionx=0;
    directiony=0;
    HasHitTarget=false;
    Active=false;

}

void Projectile::setTarget(SDL_Rect target)
{

  this->target=target;
  SetUp();

}

void Projectile::Place(SDL_Rect reference, DIRECTION dir)
{
  
  
   int x=0;
   int y=0;
   
  switch(dir)
    {
     
    case UP:
      /* x=GetCaster()->GetBaseEntity()->getPosition().x
	 +(GetCaster()->GetBaseEntity()->getPosition().w-projectile->getPosition().w)/2;*/
      x=reference.x+reference.w/2-getPosition().w;
      y=reference.y-getPosition().h+getPosition().h/2;
      break;
    case DOWN:

      x=reference.x+reference.w/2-getPosition().w;
      y=reference.y/*+getPosition().h/2*/;
      break;
    case LEFT:
           x=reference.x-getPosition().w/2;
	   y=reference.y-(reference.h-getPosition().h)/2;
      break;
    case RIGHT:
      // x=reference.x+(reference.w-getPosition().w/2);
      x=reference.x+getPosition().w/2;
	     
      y=reference.y-(reference.h-getPosition().h)/2;
      break;
      
    }
  SetPosition(x,y);

}
