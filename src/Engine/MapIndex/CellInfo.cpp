#include "CellInfo.h"


CellInfo::CellInfo(int id, ENTITY_TYPE t):id(id),type(t)
{

}


int CellInfo::getID()
{
    return id;
}

ENTITY_TYPE CellInfo::getType()
{
    return type;
}
