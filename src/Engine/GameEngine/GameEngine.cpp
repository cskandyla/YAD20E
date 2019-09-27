#include "GameEngine.h"
#include "SpellEffects.h"
#include "Camera.h"
#include "KnowledgePool.h"
#include "BaseRenderer.h"
#include <iostream>


#include "BuiltinObjective.h"

#include "Quests.h"


//#ifdef LUA_SUPPORT
#include "LuaObjective.h"
#include "Lua_Export.h"
//#endif

using std::cout;
using std::endl;


GameEngine::GameEngine(lua_State *l):l(l)
{
	cout<<"lua state:"<<l<<endl;
	lua_register_everything(this->l);
	cout<<"lua state:"<<l<<endl;
}

GameEngine::~GameEngine()
{

  delete camera;
  delete TE;

  
  cout<<"Deallocating the index"<<endl;
  MapIndex::Instance()->Free();
  KnowledgePool::Instance()->Free();
  cout<<"Deleting the map"<<endl;
  delete the_map;
  SDL_DestroyTexture(Game_Texture);
  delete Game_Surface_Rect;
  delete g_renderer;

}

bool GameEngine::Init(string XMLFile, SDL_Rect *GameScreenSurface)
{
	//
cout<<"lua state:"<<l<<endl;
  string map,mapsetting;
  XmlBuilder::ParseInit(XMLFile,map,mapsetting);
  
  camera=new Camera(GameScreenSurface,pair<int,int> (0,0));
  the_map=new Map(TILE_SIZE);
  the_map->LoadProperly((char*)map.c_str());
  cout<<"MAP LOADED"<<endl;

  //GAME SURFACE CREATION
  //  Game_Surface=SDL_CreateRGBSurface(0,the_map->getWidth()*the_map->getTileSize(),the_map->getHeight()*the_map->getTileSize(),32,rmask,gmask,bmask,amask);
  Game_Texture= SDL_CreateTexture(BaseRenderer::Instance()->Renderer(), SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET,
				  the_map->getWidth()*the_map->getTileSize(),the_map->getHeight()*the_map->getTileSize());
  SDL_SetTextureBlendMode(Game_Texture,SDL_BLENDMODE_NONE);
  Game_Surface_Rect=new SDL_Rect();
  Game_Surface_Rect->x=0;
  Game_Surface_Rect->y=0;
  Game_Surface_Rect->w=the_map->getWidth()*the_map->getTileSize();
  Game_Surface_Rect->h=the_map->getHeight()*the_map->getTileSize();
  //KnowledgeBase
  KnowledgePool::Instance()->Init();
  
  //MAPINDEX
  MapIndex::Instance()->Init(the_map);
  XmlBuilder::LoadTeams(XMLFile);

  int visibility=0;
  cout<<"Parsing mapsetting"<<endl;
  XmlBuilder::ParseMapSetting(mapsetting,visibility);

  //RENDERER
  g_renderer=new GameRenderer(visibility,camera);
  //MAIN CHARACTER
   the_char=KnowledgePool::Instance()->getCharacter(1);
  //VISION
  MapIndex::Instance()->ComputeVision(the_char->getPosition());
  cout<<"lua state:"<<l<<endl;
  luaL_dofile(l,"Resources/init.lua");
  cout<<"lua state:"<<l<<endl;
  Quest *loaded_quest=XmlBuilder::LoadQuest(mapsetting,l);
  //TODO Realm, group the Map, Characters and Quest in one compact Realm, to clean up turn engine and optimizations

  
  //TURN ENGINE
  TE=new TurnEngine(camera,loaded_quest);
  return true;
}


void GameEngine::Draw(SDL_Texture *maintexture)
{
  g_renderer->Draw(the_char->getPosition(),Game_Texture,TE->GetTurn());

  //this is actually static until we switch maps maybe we should keep it as a class variable so as to not recreate it everytime we run
  SDL_Rect window;
  window.x=0;
  window.y=0;
  window.w=(Game_Surface_Rect->w>camera->GetCam()->w)?camera->GetCam()->w:Game_Surface_Rect->w;
  window.h=(Game_Surface_Rect->h>camera->GetCam()->h)?camera->GetCam()->h:Game_Surface_Rect->h;
   
  BaseRenderer::Instance()->RenderTexture(Game_Texture,maintexture,getViewpoint(),&window);
}

void GameEngine::Update(float time)
{
  TE->Update(time);
  //Updating the camera doesnt seem to fit here.
  int x=(the_char->getPosition().x+the_char->getPosition().w/2-camera->GetCam()->w/2);
  int y=(the_char->getPosition().y+the_char->getPosition().h/2-camera->GetCam()->h/2);
  camera->Set(x,y);
  if(camera->Get().first>(MapIndex::Instance()->getMap()->getWidth()* MapIndex::Instance()->getMap()->getTileSize()-camera->GetCam()->w))
    camera->Set(MapIndex::Instance()->getMap()->getWidth()* MapIndex::Instance()->getMap()->getTileSize()-camera->GetCam()->w,camera->Get().second);
  if(camera->Get().second>(MapIndex::Instance()->getMap()->getHeight()* MapIndex::Instance()->getMap()->getTileSize()-camera->GetCam()->h))
    camera->Set(camera->Get().first,MapIndex::Instance()->getMap()->getHeight()* MapIndex::Instance()->getMap()->getTileSize()-camera->GetCam()->h);
    
  if(camera->Get().first<0)
    {
      camera->Set(0,camera->Get().second);
    }
  if(camera->Get().second<0)
    {
      camera->Set(camera->Get().first, 0);
    }
}


void GameEngine::Handle_Events(SDL_Event *event)
{
 
  TE->Handle_Events(event);
}

TurnEngine* GameEngine::getTurnEngine()
{
  return this->TE;
}


Camera* GameEngine::getCamera()
{
  return camera;
}

SDL_Rect*    GameEngine::getViewpoint()
{
  SDL_Rect* vp=new SDL_Rect();
  vp->x=camera->Get().first;
  vp->y=camera->Get().second;
  vp->w=(Game_Surface_Rect->w>camera->GetCam()->w)?camera->GetCam()->w:Game_Surface_Rect->w;
  vp->h=(Game_Surface_Rect->h>camera->GetCam()->h)?camera->GetCam()->h:Game_Surface_Rect->h;
  return vp;
}
