#include <SDL2/SDL.h>
#include <vector>
#include <string>
#include <unordered_map>
using std::vector;
using std::pair;
using std::string;

using std::unordered_map;
#include "tile.h"
#include "Trigger.h"
#ifndef __MYMAP__
#define __MYMAP__

enum TILEMAP_LAYER {LGROUND=0,LOBJECT,LCOLISION};
enum TILEMAP_SHOW {SGROUND=0,SOBJECT,SCOLISION,SCELLS,SALL,SALLOWED,SVISIBLE};
class Map
{

private:
    int width;
    int height;
    int tilesize;
    int lastid;
    vector< vector <Tile*> > groundtiles;
    vector< vector <Tile*> > objecttiles;
    vector<vector<Tile*> > CollisionTiles;
    unordered_map <int,pair<string,SDL_Texture*> > groundsurfaces;
    unordered_map <int,pair<string,SDL_Texture*> > objectsurfaces;
    unordered_map <int,pair<string,SDL_Texture*> > ColisionSurfaces;
    vector<Trigger*> Triggers;
    bool showtriggers;

    TILEMAP_SHOW toshow;
public:
    Map(int tilesize);
    virtual ~Map();

    void Show(SDL_Texture *screen);
    void Save(char *file);
    
    void AddSurface(string surf,TILEMAP_LAYER t);
    void Set(int i,int j,int surfid,TILEMAP_LAYER t);
    
    void Fill(int surfid,TILEMAP_LAYER t);
    void FillNew(int surfid,TILEMAP_LAYER t,int width,int height);
    void Load(char *file);
    void LoadProperly(char *file);
    void SetVisibleLayer(TILEMAP_SHOW t);
    void DisplayTriggers(bool d)
    {
        showtriggers=d;
    }
    void LoadTilesFromDirectory(string directory,TILEMAP_LAYER t);
    int getWidth()
    {
        return width;
    }
    int getHeight()
    {
        return height;
    }
    int getTileSize()
    {
        return tilesize;
    }
    void AddTrigger(Trigger *t);
    Tile* getTile(int x,int y,TILEMAP_LAYER tl);
    vector<vector<Tile*> > getCollisionTiles()
    {
        return CollisionTiles;
    }
    vector<vector<Tile*> > getObjectTiles()
    {
        return objecttiles;
    }

    vector<vector<Tile*> > getGroundTiles()
    {
        return groundtiles;

    }
    SDL_Texture* GetSurface(int x,int y,TILEMAP_LAYER tl);
    TILEMAP_SHOW getLayerstoShow()
    {
        return toshow;
    }


};
#endif // __MYMAP__
