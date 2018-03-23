#include "State_Wander.h"


Wander::Wander()
{

}


void Wander::Execute(AIEntity *the_char)
{
    list<DIRECTION> p;
    for(int i=0; i<8; i++)
    {
        int next_move=1;

        if(next_move==0)
        {
            if((the_char->getCharacter()->getPosition().x/TILE_SIZE)-i>=0)
                if( MapIndex::Instance()->IsPathable((the_char->getCharacter()->getPosition().x/TILE_SIZE)-i,the_char->getCharacter()->getPosition().y/TILE_SIZE))
                    p.push_back(LEFT);
        }

        else if(next_move==1)
        {

            if( MapIndex::Instance()->IsPathable((the_char->getCharacter()->getPosition().x/TILE_SIZE)+i,the_char->getCharacter()->getPosition().y/TILE_SIZE))
                p.push_back(RIGHT);
        }
        else if(next_move==2)
        {
            p.push_back(UP);
        }
        else
        {
            p.push_back(DOWN);
        }
    }

    the_char->getCharacter()->Move(p);


}
