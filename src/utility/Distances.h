#include <utility>
#include <cmath>
using std::pair;

#ifndef __DISTANCES_H
#define __DISTANCES_H

class Distances
{
 public:
static int Manhattan_Distance(pair<int,int> P1,pair<int,int>P2);

static int Eucledian_Distance(pair<int,int> P1,pair<int,int>P2);
};
#endif // __DISTANCES_H
