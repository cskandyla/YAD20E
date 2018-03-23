#include <utility>
#include "MapIndex.h"
//Use mapindex to discern if a tile is pathable

#ifndef __ASTAR__
#define __ASTAR__


struct pairhash
{
public:
    template <typename T, typename U>
    std::size_t operator()(const std::pair<T, U> &x) const
    {
        return std::hash<T>()(x.first) ^ std::hash<U>()(x.second);
    }
};

class AStar
{
private:

public:

    static list<DIRECTION> getPath(MapIndex *m_index,pair<int,int> start_p,pair<int,int> end_p);


};
#endif // __ASTAR__
