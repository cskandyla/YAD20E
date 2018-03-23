#include "State_Flee.h"
#include "Astar.h"
#include "Distances.h"

Flee::Flee()
{


}


void Flee::Execute(AIEntity *the_char)
{
    int max_dist = 0;
    pair<int,int> max_loc, cur_loc_examined, target_loc(target->getPosition().x/TILE_SIZE, target->getPosition().y/TILE_SIZE);
    int range=the_char->getCharacter()->getGeneralStats()->getSpeed();


    for(int i=0; i<range+1; i++)
    {
        //1
        int j=range-i;
        cur_loc_examined.first=the_char->getCharacter()->getPosition().x/TILE_SIZE+i;
        cur_loc_examined.second=the_char->getCharacter()->getPosition().y/TILE_SIZE+j;

        if(cur_loc_examined.first >= 0 && cur_loc_examined.second >=0 && cur_loc_examined.first <  MapIndex::Instance()->getMap()->getWidth()
                && cur_loc_examined.second <  MapIndex::Instance()->getMap()->getHeight()
                &&  MapIndex::Instance()->IsPathable(cur_loc_examined.second, cur_loc_examined.first)
                &&  MapIndex::Instance()->getVisible(cur_loc_examined.second, cur_loc_examined.first))
        {


	  int dist = Distances::Manhattan_Distance(target_loc, cur_loc_examined);
            if( dist > max_dist)
            {
                max_dist = dist;
                max_loc = cur_loc_examined;


            }
        }
        //2
        j=i-range;
        cur_loc_examined.first=the_char->getCharacter()->getPosition().x/TILE_SIZE+i;
        cur_loc_examined.second=the_char->getCharacter()->getPosition().y/TILE_SIZE+j;

        if(cur_loc_examined.first >= 0 && cur_loc_examined.second >=0 && cur_loc_examined.first <  MapIndex::Instance()->getMap()->getWidth()
                && cur_loc_examined.second <  MapIndex::Instance()->getMap()->getHeight()
                &&  MapIndex::Instance()->IsPathable(cur_loc_examined.second, cur_loc_examined.first)
                &&  MapIndex::Instance()->getVisible(cur_loc_examined.second, cur_loc_examined.first))
        {


	  int dist = Distances::Manhattan_Distance(target_loc, cur_loc_examined);
            if( dist > max_dist)
            {
                max_dist = dist;
                max_loc = cur_loc_examined;

            }
        }
        //3
        j=range-i;
        cur_loc_examined.first=the_char->getCharacter()->getPosition().x/TILE_SIZE-i;
        cur_loc_examined.second=the_char->getCharacter()->getPosition().y/TILE_SIZE-j;

        if(cur_loc_examined.first >= 0 && cur_loc_examined.second >=0 && cur_loc_examined.first <  MapIndex::Instance()->getMap()->getWidth()
                && cur_loc_examined.second <  MapIndex::Instance()->getMap()->getHeight()
	   &&  MapIndex::Instance()->IsPathable(cur_loc_examined.second, cur_loc_examined.first)
                &&  MapIndex::Instance()->getVisible(cur_loc_examined.second, cur_loc_examined.first))
        {


	  int dist = Distances::Manhattan_Distance(target_loc, cur_loc_examined);
            if( dist > max_dist)
            {
                max_dist = dist;
                max_loc = cur_loc_examined;

            }
        }
        //4
        j=i-range;
        cur_loc_examined.first=the_char->getCharacter()->getPosition().x/TILE_SIZE-i;
        cur_loc_examined.second=the_char->getCharacter()->getPosition().y/TILE_SIZE-j;

        if(cur_loc_examined.first >= 0 && cur_loc_examined.second >=0 && cur_loc_examined.first <  MapIndex::Instance()->getMap()->getWidth()
                && cur_loc_examined.second <  MapIndex::Instance()->getMap()->getHeight()
	   &&  MapIndex::Instance()->IsPathable(cur_loc_examined.second, cur_loc_examined.first)
                &&  MapIndex::Instance()->getVisible(cur_loc_examined.second, cur_loc_examined.first))
        {

	  int dist = Distances::Manhattan_Distance(target_loc, cur_loc_examined);
            if( dist > max_dist)
            {
                max_dist = dist;
                max_loc = cur_loc_examined;

            }
        }
    }

    pair<int,int> cur_loc(the_char->getCharacter()->getPosition().x/TILE_SIZE,the_char->getCharacter()->getPosition().y/TILE_SIZE);
    list<DIRECTION> whole_path = AStar::getPath( MapIndex::Instance(),cur_loc,max_loc);

    the_char->getCharacter()->Move(whole_path);
}



void Flee::setTarget(BaseCharacter *target)
{
    this->target=target;

}
