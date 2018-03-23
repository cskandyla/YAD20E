#include "State_Seek.h"
#include "Astar.h"
#include "Distances.h"

Seek::Seek()
{

}

void Seek::Execute(AIEntity *the_char)
{
    if(target != NULL)
    {
        Weapon *wi = dynamic_cast<Weapon*>(the_char->getCharacter()->getSlot(MainWeapon));

        if(wi!=NULL)
        {
            int min_dist = 9999;
            pair<int,int> min_loc, cur_loc_examined, cur_loc(the_char->getCharacter()->getPosition().x/TILE_SIZE, the_char->getCharacter()->getPosition().y/TILE_SIZE);
            int range=wi->getInfo()->getRange();
            //std::cout<<"range: "<<range<<std::endl;
            //std::cout<<"char: "<<the_char->getCharacter()->getPosition().x/TILE_SIZE<<','<<the_char->getCharacter()->getPosition().y/TILE_SIZE<<std::endl;
            //std::cout<<"target: "<<target->getPosition().x/TILE_SIZE<<','<<target->getPosition().y/TILE_SIZE<<std::endl;
            for(int i=0; i<=range; i++)
            {
                //1
                int j=range-i;
                cur_loc_examined.first=target->getPosition().x/TILE_SIZE+i;
                cur_loc_examined.second=target->getPosition().y/TILE_SIZE+j;
                //std::cout<<"loc_examined: "<<cur_loc_examined.first<<','<<cur_loc_examined.second<<std::endl;
                if(cur_loc_examined.first >= 0 && cur_loc_examined.second >=0 && cur_loc_examined.first <  MapIndex::Instance()->getMap()->getWidth()
                        && cur_loc_examined.second <  MapIndex::Instance()->getMap()->getHeight()
		   &&  MapIndex::Instance()->IsPathable(cur_loc_examined.second, cur_loc_examined.first)
		   &&  MapIndex::Instance()->RayTrace(cur_loc_examined.second, cur_loc_examined.first,target->getPosition().y/TILE_SIZE,target->getPosition().x/TILE_SIZE))
                {
		  //std::cout<<"loc_examined: "<<cur_loc_examined.first<<','<<cur_loc_examined.second<<std::endl;
		  int dist = Distances::Manhattan_Distance(cur_loc, cur_loc_examined);
                    if(dist <= min_dist)
                    {
                        min_dist = dist;
                        min_loc = cur_loc_examined;
//                        std::cout<<"dist: "
                    }
                }
                //2
                j=i-range;
                cur_loc_examined.first=target->getPosition().x/TILE_SIZE+i;
                cur_loc_examined.second=target->getPosition().y/TILE_SIZE+j;
                //std::cout<<"loc_examined: "<<cur_loc_examined.first<<','<<cur_loc_examined.second<<std::endl;
                if(cur_loc_examined.first >= 0 && cur_loc_examined.second >=0 && cur_loc_examined.first < MapIndex::Instance()->getMap()->getWidth()
		   && cur_loc_examined.second <  MapIndex::Instance()->getMap()->getHeight()
		   &&  MapIndex::Instance()->IsPathable(cur_loc_examined.second, cur_loc_examined.first)
		   && MapIndex::Instance()->RayTrace(cur_loc_examined.second, cur_loc_examined.first,target->getPosition().y/TILE_SIZE,target->getPosition().x/TILE_SIZE))
                {
		  //std::cout<<"loc_examined: "<<cur_loc_examined.first<<','<<cur_loc_examined.second<<std::endl;

		  int dist = Distances::Manhattan_Distance(cur_loc, cur_loc_examined);
                    if(dist <= min_dist)
                    {
                        min_dist = dist;
                        min_loc = cur_loc_examined;
                    }
                }
                //3
                j=range-i;
                cur_loc_examined.first=target->getPosition().x/TILE_SIZE-i;
                cur_loc_examined.second=target->getPosition().y/TILE_SIZE-j;
                //std::cout<<"loc_examined: "<<cur_loc_examined.first<<','<<cur_loc_examined.second<<std::endl;
                if(cur_loc_examined.first >= 0 && cur_loc_examined.second >=0 && cur_loc_examined.first <  MapIndex::Instance()->getMap()->getWidth()
                        && cur_loc_examined.second <  MapIndex::Instance()->getMap()->getHeight()
		   &&  MapIndex::Instance()->IsPathable(cur_loc_examined.second, cur_loc_examined.first)
		        &&  MapIndex::Instance()->RayTrace(cur_loc_examined.second, cur_loc_examined.first,target->getPosition().y/TILE_SIZE,target->getPosition().x/TILE_SIZE))
                {
		  //std::cout<<"loc_examined: "<<cur_loc_examined.first<<','<<cur_loc_examined.second<<std::endl;

		  int dist = Distances::Manhattan_Distance(cur_loc, cur_loc_examined);
                    if(dist <= min_dist)
                    {
                        min_dist = dist;
                        min_loc = cur_loc_examined;
                    }
                }
                //4
                j=i-range;
                cur_loc_examined.first=target->getPosition().x/TILE_SIZE-i;
                cur_loc_examined.second=target->getPosition().y/TILE_SIZE-j;
                //std::cout<<"loc_examined: "<<cur_loc_examined.first<<','<<cur_loc_examined.second<<std::endl;
                if(cur_loc_examined.first >= 0 && cur_loc_examined.second >=0 && cur_loc_examined.first <  MapIndex::Instance()->getMap()->getWidth()
                        && cur_loc_examined.second <  MapIndex::Instance()->getMap()->getHeight()
		   &&  MapIndex::Instance()->IsPathable(cur_loc_examined.second, cur_loc_examined.first)
		   &&  MapIndex::Instance()->RayTrace(cur_loc_examined.second, cur_loc_examined.first,target->getPosition().y/TILE_SIZE,target->getPosition().x/TILE_SIZE))
                {
		  //std::cout<<"loc_examined: "<<cur_loc_examined.first<<','<<cur_loc_examined.second<<std::endl;

		  int dist = Distances::Manhattan_Distance(cur_loc, cur_loc_examined);
                    if(dist <= min_dist)
                    {
                        min_dist = dist;
                        min_loc = cur_loc_examined;
                    }
                }
            }

            //std::cout<<"min loc:"<<min_loc.first<<','<<min_loc.second<<std::endl;

            list<DIRECTION> whole_path = AStar::getPath( MapIndex::Instance(),cur_loc,min_loc), actual_path;

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

}


void Seek::setTarget(BaseCharacter *t)
{
    target = t;
}
