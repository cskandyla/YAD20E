#include <SDL2/SDL.h>
#define TILE_SIZE 30
#ifndef __ENTITY__
#define __ENTITY__


class Entity
{
protected:
  SDL_Texture *tex;
  int width;
  int height;
  SDL_Rect position;
public:
  Entity(SDL_Texture  *t,int w,int h);
  Entity(const Entity &anentity);
  virtual ~Entity();
  virtual void Draw(SDL_Texture *screen);
  virtual void Update(float time);
  virtual void setPosition(int x,int y);
  void setPosition(int x,int y,int w,int h);
  void setPosition(SDL_Rect pos);
  SDL_Rect getPosition();
  SDL_Rect getRect();
  int distance(Entity *ent);
};

#endif // __ENTITY__
