#include "BasicCharacter.h"
#include "OptionsMenu.h"
#include "MapIndex.h"
#include <deque>
#include "Zombie.h"
#include "GridCells.h"
using std::deque;

#ifndef __TURN__
#define __TURN__

class Camera;
class UserInputHandler;
class Turn
{
private:
    bool Done;
    BaseCharacter* cur_char;
    Camera *camera;
    unsigned int moves;
    deque<SDL_Rect> path;
    AIEntity *ent;
    UserInputHandler *user_handler;
   
   

public:
    Turn(BaseCharacter *bchar,Camera *camera,AIEntity *ent);
    virtual ~Turn();
    void Update(float time);
    void Handle_Events(SDL_Event *event);
    bool Turn_Done();
    bool HasMoved();
    bool StandardActionDone();
    bool ReactionsDone();
    bool TurnDone();
    void SetMoved(bool Moved);
    void SetStandardAction(bool standard_action);
    void SetDone(bool Done);
    //Getters
    BaseCharacter    *TheCharacter();
    UserInputHandler *GetUserInputHandler();
    Camera           *GetCamera();
    //
    bool AIControlled();
};

#endif
