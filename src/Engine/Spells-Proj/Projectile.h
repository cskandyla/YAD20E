#include <SDL2/SDL.h>
#include "AnimatedEntity.h"
#include "MovingEntity.h"
#ifndef __PROJECTILE__
#define __PROJECTILE__
class BaseCharacter;
class AnimatedEntity;
class Projectile
{
private:
    AnimatedEntity *animentity;
    SDL_Rect target;
    bool HasHitTarget;
    bool Active;
    int velocity;
    float directionx,directiony;
    float theta;
public:
    Projectile(AnimatedEntity *animentity,SDL_Rect target,int velocity=1);
    Projectile(const Projectile &aprojectile);
    virtual ~Projectile();
    void Update(float time);
    void UpdateEllipse(float time);
    void Draw(SDL_Texture *screen);
    bool Hit();
    bool IsActive();
    void MakeActive(bool active);
    void SetPosition(int x,int y);
    SDL_Rect getPosition();
    void SetUp();
    void Reset();
    void setTarget(SDL_Rect target);
    //Places Projectile in reference to a rect and a direction
    void Place(SDL_Rect reference,DIRECTION dir);

};
#endif // __PROJECTILE__
