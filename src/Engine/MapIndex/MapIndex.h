#include "map.h"
#include "BasicCharacter.h"
#include "CellInfo.h"
#include "Distances.h"
#include "Doodad.h"
#include <string>
#include <sstream>
#include <map>
using std::string;
#include <unordered_map>
using std::vector;
using std::pair;
using std::string;



#ifndef __MAPINDEX__
#define __MAPINDEX__


//instantiation for pair<int,int> to create an unordered map
class mapindex_hash
{
public:
  std::size_t operator () (const std::pair<int,int> &p) const;
};


class MapIndex
{
private:
    Map *themap;
    unordered_map<pair<int,int>,CellInfo*,mapindex_hash> informationgrid;
    //vector<vector<CellInfo*> > informationgrid;
    vector<vector<bool> > visibilityvector;
    vector<pair<int,int > > Walls;
    static MapIndex* m_index;
    MapIndex();
    //Doodads
    unordered_map<unsigned int,Doodad*> doodads;
public:
    static MapIndex* Instance();
    
    void Init(Map *themap);
    void Free();//Free allocated slots
    
    //Info
    string getTileInfo(int x,int y);
    ENTITY_TYPE getTileContent(int x,int y);

    //Getters
    Map* getMap();

    
    
    
		
    //Operations
    bool AddCharacter(BaseCharacter *bchar);
    bool RemoveCharacter(unsigned int id);
    bool AddItem(Item *it);
    bool RemoveItem(unsigned int id);
    bool AddDoodad(Doodad *doodad);
    bool RemoveDoodad(unsigned int id);
    bool CharIndexUpdate(BaseCharacter *selected,int xpos,int ypos);
    bool ItemIndexUpdate(Item *item,int xpos,int ypos);
	bool DoodadIndexUpdate(Doodad *doodad,int xpos,int ypos,int visibility);

    Doodad* getDoodad(unsigned int id);
    std::unordered_map<unsigned int,Doodad*>& getDoodads();
    
    //VISION
    bool Mark(int y,int x);
    bool RayTrace (int y1, int x1, int y2, int x2);
    bool MarkPath (int y1, int x1, int y2, int x2);
    bool RayTest(int y,int x);
    void ComputeVision(SDL_Rect center);
    bool getVisible(int x,int y);
    //UTILITY
    bool RectCollides(SDL_Rect big,SDL_Rect small);
    bool IsWall(int x,int y);
    bool VisionBlocking(int x,int y);
    
    bool IsPathable(int x,int y);
    bool IsVisible(int x,int y);

    //Searching
    CellInfo*             getCell(int x,int y);
    vector<CellInfo*>     getEntitiesInRange(int xpos,int ypos,int radius);
    vector<CellInfo*>     getEntitiesInLine(int xpos,int ypos,int width,DIRECTION dir);
    vector<pair<int,int>> getTilesInRange(int xpos,int ypos,int radius,bool include_entities);

};
#endif // __MAPINDEX__
