#include "tile.h"


Tile::Tile(int id)
{
    this->ID=id;

}


void Tile::setID(int id)
{
    this->ID=id;
}

int Tile::getID()
{
    return this->ID;
}
