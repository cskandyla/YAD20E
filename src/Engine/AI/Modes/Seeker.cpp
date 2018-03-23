
#include "Seeker.h"
#include "Astar.h"
#include "State_Wait.h"
#include "State_Flee.h"
#include "State_Seek.h"
#include "State_Attack.h"
#include "Distances.h"



Seeker_AI::Seeker_AI(BaseCharacter *the_char): AIEntity(the_char)
{
    this->cur_state=NULL;
    this->target = NULL;
  the_char->SetMoved(false);
              the_char->SetActionDone(false);

    Wait *wait = new Wait();
    Seek *seek = new Seek();
    Flee *flee = new Flee();
    Attack *atk = new Attack();

    AddState("STOP",wait);
    AddState("SEEK",seek);
    AddState("ATTACK",atk);
    AddState("RUN",flee);
}

Seeker_AI::Seeker_AI(BaseCharacter* the_char, AIState* starting_state): AIEntity (the_char,starting_state)
{
  this->cur_state=starting_state;
  this->target=NULL;
  the_char->SetMoved(false);
  the_char->SetActionDone(false);

    Wait *wait = new Wait();
    Seek *seek = new Seek();
    Flee *flee = new Flee();
    Attack *atk = new Attack();

    AddState("STOP",wait);
    AddState("SEEK",seek);
    AddState("ATTACK",atk);
    AddState("RUN",flee);
}



void Seeker_AI::Update()
{
    if(cur_state!=NULL && target!=NULL)
    {
      pair<int,int> current_pair(getCharacter()->getPosition().x/TILE_SIZE,getCharacter()->getPosition().y/TILE_SIZE);
      pair<int,int> target_pair(target->getPosition().x/TILE_SIZE, target->getPosition().y/TILE_SIZE);

        if(target->getGeneralStats()->getHp()>0 && MapIndex::Instance()->RayTrace(current_pair.second,current_pair.first,target->getPosition().y/TILE_SIZE,target->getPosition().x/TILE_SIZE))
        {
	  if(ActionFinished() &&  !the_char->Moved())
            {

	      if(getCharacter()->getGeneralStats()->getHp() > getCharacter()->getOriginalStats()->getHp()/2 )
                    {

                        WeaponInfo *wi = dynamic_cast<WeaponInfo*>(getCharacter()->getSlot(MainWeapon)->getInfo());

                        if(wi!=NULL)
                        {
			  if(int dist = Distances::Manhattan_Distance(current_pair, target_pair) == wi->getRange() )
                            {
                                ChangeState("ATTACK");
				the_char->SetActionDone(true);
                            }
			    else
			      {
				ChangeState("SEEK");
			      }
                        }
                    }
                    else
                    {
		      if(true /*getM_Index()->getVisible(target->getPosition().y/TILE_SIZE,target->getPosition().x/TILE_SIZE)*/)
                            ChangeState("RUN");
                        else
                        {

                            ChangeState("STOP");
                            // SOMETHING BUGGED HERE called STOP when target was visible but code said he was not visible
                        }
                    }
                    cur_state->Execute(this);
		    the_char->SetMoved(true);



            }
	  if(ActionFinished() && the_char->Moved()  && !the_char->ActionDone())
            {
                 MapIndex::Instance()->CharIndexUpdate(getCharacter(),0,0);


                    if(cur_state == getState("RUN"))
                    {
                        if(! MapIndex::Instance()->getVisible(target->getPosition().y/TILE_SIZE,target->getPosition().x/TILE_SIZE))
                        {

                            ChangeState("STOP");

                        }
                    }
                    else
                    {

                        Weapon *wi = dynamic_cast<Weapon*>(getCharacter()->getSlot(MainWeapon));

                        if(wi!=NULL)
			  {   int dist = Distances::Manhattan_Distance(current_pair, target_pair);
                            if( dist== wi->getInfo()->getRange() )
                            {
                                ChangeState("ATTACK");
                            }
                        }
                    }
                    cur_state->Execute(this);
		    the_char->SetActionDone(true);



            }

        }

         else
                {
                    ChangeState("STOP");

		    the_char->SetMoved(true);
		    the_char->SetActionDone(true);

                }
    }

}


void Seeker_AI::setTarget(BaseCharacter *target)
{
    this->target = target;
    ((Seek*) getState("SEEK"))->setTarget(target);
    ((Attack*) getState("ATTACK"))->setTarget(target);
    ((Flee*) getState("RUN"))->setTarget(target);
    ChangeState("SEEK");
}
