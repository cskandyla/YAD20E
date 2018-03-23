#include "Astar.h"
#include <set>
#include <queue>
#include <unordered_map>
#include <cmath>
#include "Distances.h"
using namespace std;


typedef pair< int, pair<int,int> > Point2dcost;



list<DIRECTION> AStar::getPath(MapIndex *m_index,pair<int, int> start_p, pair<int, int> end_p)
{
    std::priority_queue<Point2dcost,vector< Point2dcost >, std::greater< Point2dcost > >  Openlist;
    std::set<pair<int,int> > Closedlist;
    Point2dcost current;
    pair<int,int> left,right,up,down;
    std::unordered_map< pair<int,int> ,pair<int,int> ,pairhash> Parent;
    std::unordered_map< pair<int,int> , int ,pairhash> current_cost;

    // Parent[start_p]=start_p;
    current_cost[start_p]=0;
    Openlist.emplace(0,start_p);
    while(Openlist.size()>0)
    {
     
        current=Openlist.top();

        if(current.second==end_p)
        {
            break;
        }
        Openlist.pop();
        Closedlist.insert(current.second);
	
        int cost=current_cost[Parent[current.second]]+1;


	

        left.first=current.second.first-1;
        left.second=current.second.second;
        if(m_index->IsPathable(left.second,left.first))
            if(current_cost.find(left)==current_cost.end()  || cost<current_cost[left] )
            {
	      int priority=cost+Distances::Eucledian_Distance(left,end_p);//+HEURISTIC

                Openlist.emplace(priority,left);
                Parent[left]=current.second;
                current_cost[left]=cost;
            }
	//RIGHT

        right.first=current.second.first+1;
        right.second=current.second.second;
        if(m_index->IsPathable(right.second,right.first))
            if(current_cost.find(right)==current_cost.end()  || cost<current_cost[right] )
            {
	      int priority=cost+Distances::Eucledian_Distance(right,end_p);//+HEURISTIC;//+HEURISTIC
                Openlist.emplace(priority,right);
                Parent[right]=current.second;
                current_cost[right]=cost;
            }

	//UP

        up.first=current.second.first;
        up.second=current.second.second-1;
        if(m_index->IsPathable(up.second,up.first))
            if(current_cost.find(up)==current_cost.end()  || cost<current_cost[up] )
            {
	      int priority=cost+Distances::Eucledian_Distance(up,end_p);//+HEURISTIC;//+HEURISTIC
                Openlist.emplace(priority,up);
                Parent[up]=current.second;
                current_cost[up]=cost;
            }

	//DOWN

        down.first=current.second.first;
        down.second=current.second.second+1;
        if(m_index->IsPathable(down.second,down.first))
            if(current_cost.find(down)==current_cost.end()  || cost<current_cost[down] )
            {
	      int priority=cost+Distances::Eucledian_Distance(down,end_p);//+HEURISTIC;//+HEURISTIC
                Openlist.emplace(priority,down);
                Parent[down]=current.second;
                current_cost[down]=cost;
            }

    }

    pair<int,int> current_p=end_p;

    list<DIRECTION> l;

     while(Parent.find(current_p)!=Parent.end() && current_p!=start_p)
       {
	 
        if(current_p.first<Parent[current_p].first)
        {
            l.push_front(LEFT);
        }
        else if(current_p.first>Parent[current_p].first)
        {
            l.push_front(RIGHT);
        }
        else if(current_p.second<Parent[current_p].second)
        {
            l.push_front(UP);
        }
        else if(current_p.second>Parent[current_p].second)
        {
            l.push_front(DOWN);
        }
	current_p=Parent[current_p];
	
       }       
    return l;
}
