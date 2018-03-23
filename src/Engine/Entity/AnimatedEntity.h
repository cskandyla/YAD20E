#include <vector>
#ifndef __ANIMENTITY__
#define __ANIMENTITY__
#include "../Animation/animation.h"
#include "MovingEntity.h"

enum ANIMS
{
    STAND_U=0,
    STAND_L,
    STAND_D,
    STAND_R,
    WALK_U,
    WALK_L,
    WALK_D,
    WALK_R,
    THRUST_U,
    THRUST_L,
    THRUST_D,
    THRUST_R,
    SLASH_U,
    SLASH_L,
    SLASH_D,
    SLASH_R,
    SHOOT_U,
    SHOOT_L,
    SHOOT_D,
    SHOOT_R,
    CAST_U,
    CAST_L,
    CAST_D,
    CAST_R,
    DYING_A,
    DEAD_A

};
enum ANIMLOOP {YES,NO};
using std::vector;
class AnimatedEntity:public MovingEntity
{

private:
    Anim *cur_anim;
    vector<Anim*> animations;
    ANIMLOOP animloop;
public:


    AnimatedEntity(SDL_Texture *t,int w,int h);
    AnimatedEntity(const AnimatedEntity &anentity);
    virtual ~AnimatedEntity();
    bool LoadAnimations(char *file);
    void LoadAnimations(/*vector<Animation*> anims*/);
    
    virtual void Update(float time);
    void Draw(SDL_Texture *screen);
    void DrawAt(int x,int y,SDL_Texture *screen);
    void DrawFrame(int framenum,int x,int y,SDL_Texture *screen);

    //void setAnimation(Anim *anim);
    void setAnimation(ANIMS a);
    void setAnimation(int animnum);
    void setAnimLoop(ANIMLOOP animloop);
    Anim* getCur_Anim()
    {
        return cur_anim;
    }
    int getNumAnims()
    {
        return animations.size();
    }



};
#endif // __ANIMENTITY__
