#include "Distances.h"

using std::abs;
int Distances::Manhattan_Distance(pair<int,int> P1,pair<int,int>P2)
{

    return abs(P1.first-P2.first)+abs(P1.second-P2.second);

}

int Distances::Eucledian_Distance(pair<int,int> P1,pair<int,int>P2)
{
    return sqrt(pow(P2.first - P1.first, 2)+pow(P2.second - P1.second, 2));
}
