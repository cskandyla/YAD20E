#include "Renderer.h"
#include "UserInputHandler.h"
#include "KnowledgePool.h"
#include "BaseRenderer.h"
#include "WallSpell.h"
#include "Caster.h"
#include "DrawableElement.h"
#include <algorithm>

GameRenderer::GameRenderer(int visibility, Camera *camera):visibility(visibility),camera(camera)
{
  cursor_tile=new DrawableTile(0,0,MapIndex::Instance()->getMap()->getTileSize(),SDL_Color{255,0,0},127);
  available_tile=new DrawableTile(0,0,MapIndex::Instance()->getMap()->getTileSize(),SDL_Color{0,255,0},127);
}

GameRenderer::~GameRenderer()
{

  delete cursor_tile;
  delete available_tile;
}

void GameRenderer::ShowCursor(SDL_Texture *screen,Turn *the_turn)
{
  Map *themap=MapIndex::Instance()->getMap();
  int tile_size=themap->getTileSize();
  int x,y;
  SDL_GetMouseState(&x,&y);
  pair<int,int> translated_pos=camera->Translate(x,y);
  if(translated_pos.first>=0 && translated_pos.second>=0 &&
     translated_pos.first<themap->getWidth()*themap->getTileSize() && translated_pos.second<themap->getHeight()*themap->getTileSize())
    {
      if(the_turn->GetUserInputHandler() && the_turn->GetUserInputHandler()->GetState())
	{
	  vector<pair<int,int>> target_tiles=the_turn->GetUserInputHandler()->GetState()->GetAoeTiles();
	  for(int i=0;i<target_tiles.size();i++)
	    {
	      cursor_tile->Draw(target_tiles[i].first*tile_size+translated_pos.first,target_tiles[i].second*tile_size+translated_pos.second,screen);
	    }
	}
    }
}


void GameRenderer::Draw(SDL_Rect center,SDL_Texture *screen,Turn *the_turn)
{

  //if we're not moving the camera we dont need to redraw the map so... maybe dont ?
  Map *themap=MapIndex::Instance()->getMap();
  int tile_size=themap->getTileSize();
  int starti=center.x/themap->getTileSize();
  int startj=center.y/themap->getTileSize();    
    
  SDL_Rect pos;
  pos.x=0;
  pos.y=0;
  pos.w=themap->getTileSize();
  pos.h=themap->getTileSize();
  //Static Map

  SDL_SetRenderTarget(BaseRenderer::Instance()->Renderer(),screen);
  SDL_RenderClear(BaseRenderer::Instance()->Renderer());
    
    
  for(int i=starti+visibility; i>=starti-visibility; i--)
    for(int j=startj+visibility; j>=startj-visibility; j--)
      {
	int x=starti+visibility-i;
	int y=startj+visibility-j;
	if(i>=0 && j>=0 && i<themap->getWidth() && j<themap->getHeight() && MapIndex::Instance()->getVisible(j,i))
	  {
	    pos.x=i*themap->getTileSize();
	    pos.y=j*themap->getTileSize();
	    if(themap->getLayerstoShow()==SALL || themap->getLayerstoShow()==SGROUND || themap->getLayerstoShow()==SVISIBLE)
	      {
		BaseRenderer::Instance()->Render(themap->GetSurface(j,i,LGROUND),&pos);
	      }
	    if(themap->getLayerstoShow()==SALL || themap->getLayerstoShow()==SOBJECT || themap->getLayerstoShow()==SVISIBLE)
	      {
		//dont draw the blank tile :) -- make sure our mapeditor allways passes the blank tile as 0
		if(themap->getTile(j,i,LOBJECT)->getID()!=0)
		  BaseRenderer::Instance()->Render(themap->GetSurface(j,i,LOBJECT),&pos);
	      }
	    if(themap->getLayerstoShow()==SALL || themap->getLayerstoShow()==SCOLISION)
	      {
		//dont draw the blank tile :) -- make sure our mapeditor allways passes the blank tile as 0
		if(themap->getTile(j,i,LCOLISION)->getID()!=0)
		  BaseRenderer::Instance()->Render(themap->GetSurface(j,i,LCOLISION),&pos);
	      }
	  }
      }
   
    
  SDL_SetRenderTarget(BaseRenderer::Instance()->Renderer(),NULL);

    
  //Show Targeted Tile and the available moves/aoe indicator 
  if(the_turn->GetUserInputHandler() && the_turn->GetUserInputHandler()->GetState())
    {
      vector<pair<int,int> > available_tiles=the_turn->GetUserInputHandler()->GetState()->GetTiles();
      for(int i=0;i<available_tiles.size();i++)
	{
	  //make sure to only include tiles we can actually see -- should turn this into an actual cover implementation once cover is implemented...
	  if(MapIndex::Instance()->RayTrace(the_turn->TheCharacter()->getPosition().y/tile_size,the_turn->TheCharacter()->getPosition().x/tile_size,available_tiles[i].first,available_tiles[i].second))
	    available_tile->Draw(available_tiles[i].second*themap->getTileSize(),available_tiles[i].first*themap->getTileSize(),screen);
	}
	  
      int tile_size=themap->getTileSize();
      int x,y;
      SDL_GetMouseState(&x,&y);
      pair<int,int> translated_pos=camera->Translate(x,y);
	
      translated_pos.first/=tile_size;
      translated_pos.second/=tile_size;
      //if our cursor is in the available tiles area and we can raytrace to that tile, then show the area of effect
      if(std::find(available_tiles.begin(),available_tiles.end(),pair<int,int>(translated_pos.second,translated_pos.first))!=available_tiles.end() )
	//&& MapIndex::Instance()->RayTrace(the_turn->TheCharacter()->getPosition().y/tile_size,the_turn->TheCharacter()->getPosition().x/tile_size,translated_pos.second,translated_pos.first))	  
      {
	ShowCursor(screen,the_turn);
      }
	  
    }
    
    
  //Dynamic Map find a way to handle	
  DrawDynamicEntities(starti,startj,screen);
    
}


void GameRenderer::DrawDynamicEntities(int starti,int startj,SDL_Texture *screen)
{
  Map *themap=MapIndex::Instance()->getMap();
  int tile_size=themap->getTileSize();
  vector<DrawableElement> dyn_elements;
  for(int i=starti-visibility; i<starti+visibility; i++)
    for(int j=startj-visibility; j<startj+visibility; j++)
      {
	//Reconfigure to Place active  Character over anything else pass turn? -- Draw last // order by y 
	if(i>=0 && j>=0 && i<themap->getWidth() && j<themap->getHeight() &&  MapIndex::Instance()->getVisible(j,i))
	  {
	    CellInfo *cinfo= MapIndex::Instance()->getCell(j,i);
	    if(cinfo!=NULL && cinfo->getType()==CHARACTER_T /* && KnowledgePool::Instance()->getCharacter(cinfo->getID())!=the_turn->TheCharacter()*/)
	      {
		//KnowledgePool::Instance()->getCharacter(cinfo->getID())->Draw(screen);//->
		
		int zindex=0;
		pair<int,int> c_pos(KnowledgePool::Instance()->getCharacter(cinfo->getID())->getPosition().x/tile_size,KnowledgePool::Instance()->getCharacter(cinfo->getID())->getPosition().y/tile_size);
		if(KnowledgePool::Instance()->getCharacter(cinfo->getID())->getGeneralStats()->getHp()<=0)
		  zindex=-1;
		DrawableElement elem(zindex,c_pos,KnowledgePool::Instance()->getCharacter(cinfo->getID()),D_CHARACTER);
		dyn_elements.push_back(elem);
		//also add all wallspells
		Caster *caster=dynamic_cast<Caster*>(KnowledgePool::Instance()->getCharacter(cinfo->getID()));
		if(caster)
		  {
		    for(int k=0;k<caster->GetEotSpells().size();k++)
		      {
			WallSpell *wall_spell=dynamic_cast<WallSpell*>(caster->GetEotSpells()[k]);
			if(wall_spell)
			  {
			    pair<int,int> pos=wall_spell->GetSpellStats()->GetTarget();
			    pos.first=pos.first/tile_size;
			    pos.second=(pos.second/tile_size);//-wall_spell->GetSpellStats()->GetRadius()/2;
			    DrawableElement spell_elem(0,pos,wall_spell,D_WALLSPELL);
			    dyn_elements.push_back(spell_elem);			    
			  }
		      }
		  }
	      }
	    else if(cinfo!=NULL && cinfo->getType()==OBJECT_T)
	      {
		DrawableElement elem(0,pair<int,int>(i,j),KnowledgePool::Instance()->getItem(cinfo->getID()),D_ITEM);
		dyn_elements.push_back(elem);
	      }
	    else if(cinfo!=NULL && cinfo->getType()==DOODAD_T)
	      {
		MapIndex::Instance()->getDoodad(cinfo->getID())->Draw(screen);
	      }
	  }
      }
  std::sort(dyn_elements.begin(),dyn_elements.end(),sort_dynamic_map_elementsz);

  for(int i=0;i<dyn_elements.size();i++)
    {
      if(dyn_elements[i].GetObjectType()==D_CHARACTER)
	{
	  ((BaseCharacter*)dyn_elements[i].GetObject())->Draw(screen);
	}
      else if(dyn_elements[i].GetObjectType()==D_ITEM)
	{
	  ((VisibleItem*)dyn_elements[i].GetObject())->Draw(screen);
	}
      else if(dyn_elements[i].GetObjectType()==D_WALLSPELL)
	{
	  ((WallSpell*)dyn_elements[i].GetObject())->Draw(screen);
	}
    }
}



