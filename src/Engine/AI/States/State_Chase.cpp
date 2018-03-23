#include "State_Chase.h"
#include "Astar.h"
#include "Distances.h"


Chase::Chase()
{

}
void Chase::Execute(AIEntity* the_char)
{
    //MOVE TO A SQUARE ADJACENT TO THE TARGET IF POSSIBLE
    if(target != NULL)
    {

        int upper=1000, downer=1000,lefter=1000, righter=1000;
        pair<int,int> up( target->getPosition().x/TILE_SIZE,target->getPosition().y/TILE_SIZE -1)
        ,down( target->getPosition().x/TILE_SIZE,target->getPosition().y/TILE_SIZE +1)
        ,left( target->getPosition().x/TILE_SIZE -1,target->getPosition().y/TILE_SIZE)
        ,right( target->getPosition().x/TILE_SIZE +1,target->getPosition().y/TILE_SIZE);

        if( MapIndex::Instance()->IsPathable(up.second, up.first))
	  upper = Distances::Manhattan_Distance(pair<int,int> (the_char->getCharacter()->getPosition().x/TILE_SIZE,the_char->getCharacter()->getPosition().y/TILE_SIZE),up);
        if( MapIndex::Instance()->IsPathable(down.second, down.first))
	  downer = Distances::Manhattan_Distance(pair<int,int> (the_char->getCharacter()->getPosition().x/TILE_SIZE,the_char->getCharacter()->getPosition().y/TILE_SIZE),down);
        if( MapIndex::Instance()->IsPathable(left.second, left.first))
	  lefter = Distances::Manhattan_Distance(pair<int,int> (the_char->getCharacter()->getPosition().x/TILE_SIZE,the_char->getCharacter()->getPosition().y/TILE_SIZE),left);
        if( MapIndex::Instance()->IsPathable(right.second, right.first))
	  righter = Distances::Manhattan_Distance(pair<int,int> (the_char->getCharacter()->getPosition().x/TILE_SIZE,the_char->getCharacter()->getPosition().y/TILE_SIZE),right);

        int minimum = upper;
        pair<int,int> mini = up;

        if (downer <= minimum)
        {
            minimum = downer;
            mini = down;
        }

        if (lefter <= minimum)
        {
            minimum = lefter;
            mini = left;
        }

        if (righter <= minimum)
        {
            minimum = righter;
            mini = right;
        }
        pair<int,int> start_p(the_char->getCharacter()->getPosition().x/TILE_SIZE,the_char->getCharacter()->getPosition().y/TILE_SIZE);
        list<DIRECTION> whole_path = AStar::getPath( MapIndex::Instance(),start_p,mini), actual_path;

        int speed = the_char->getCharacter()->getGeneralStats()->getSpeed();
        if(speed > whole_path.size())
        {
            speed = whole_path.size();
        }

        for(int i=0; i<speed; i++)
        {
            actual_path.push_back(whole_path.front());
            whole_path.pop_front();
        }


        the_char->getCharacter()->Move(actual_path);

    }

}

void Chase::setTarget(BaseCharacter *t)
{
    target = t;
}



