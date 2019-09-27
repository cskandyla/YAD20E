#include "MapIndex.h"
#include "KnowledgePool.h"
#include <iostream>


std::size_t mapindex_hash::operator () (const std::pair<int,int> &p) const
{
	//practically copying boost
        size_t h1 = std::hash<int>{}(p.first);
        size_t h2 = std::hash<int>{}(p.second);
        size_t seed = 0;
	hash<int> h;
	seed ^= h1 + 0x9e3779b9 + (seed << 6) + (seed >> 2); 
	seed ^= h2 + 0x9e3779b9 + (seed << 6) + (seed >> 2);
        return seed;  
}


//SINGLETON
MapIndex* MapIndex::m_index=NULL;

//ALLWAYS EMPTY
MapIndex::MapIndex()
{
}

MapIndex* MapIndex::Instance()
{

	if(!m_index)
		m_index=new MapIndex();
	return m_index;
}

void MapIndex::Init(Map *themap)
{
	this->themap=themap;
	visibilityvector.resize(themap->getWidth());
	for(int i=0; i<visibilityvector.size(); i++)
	{
		visibilityvector[i].resize(themap->getHeight());

	}

	for(int i=0; i<visibilityvector.size(); i++)
		for(int j=0; j<visibilityvector.size(); j++)
		{

			visibilityvector[i][j]=false;
		}

	for(int i=0; i<themap->getWidth(); i++)
	{
		for(int j=0; j<themap->getHeight(); j++)
		{

			if(IsWall(j,i))
			{
				Walls.push_back(pair<int,int>(i,j));
			}
		}
	}

}
void MapIndex::Free()
{
	cout<<"Deleting Cells"<<endl;
	/*
	  for(int i=0;i<informationgrid.size();i++)
	  {
	  for(int j=0;j<informationgrid[i].size();j++)
	  {
	  if(informationgrid[i][j])
	  {
	  delete informationgrid[i][j];
	  }
	  }

	  }*/
  
  
}


string MapIndex::getTileInfo(int x, int y)
{
	std::stringstream s;
	int xindex=x/themap->getTileSize()*themap->getTileSize()/themap->getTileSize();
	int yindex=y/themap->getTileSize()*themap->getTileSize()/themap->getTileSize();
	/*
	  if(informationgrid[yindex][xindex]==NULL)
	  s<<"Coords: "<<x<<','<<y<<" Tile:"<<yindex<<","<<xindex<<" "<<themap->getCollisionTiles()[yindex][xindex]->getID()<<" Nothing Here";
	  else if(informationgrid[yindex][xindex]->getType()==OBJECT_T)
	  {
	  s<<KnowledgePool::Instance()->getItem(informationgrid[yindex][xindex]->getID())->getInfo()->getName();;
	  }
	  else if(informationgrid[yindex][xindex]->getType()==CHARACTER_T)
	  {
	  s<<KnowledgePool::Instance()->getCharacter(informationgrid[yindex][xindex]->getID())->getInfo()->getName();
	  }*/

	return s.str();
}

  
ENTITY_TYPE MapIndex::getTileContent(int x,int y)
{
	int xindex=x/themap->getTileSize()*themap->getTileSize()/themap->getTileSize();
	int yindex=y/themap->getTileSize()*themap->getTileSize()/themap->getTileSize();
	/*
	  if(informationgrid[yindex][xindex]!=NULL)
	  {

	  return informationgrid[yindex][xindex]->getType();
	  }*/
	if(informationgrid.find(pair<int,int>(yindex,xindex))!=informationgrid.end())
	{
		return informationgrid[pair<int,int>(yindex,xindex)]->getType();
	}
	else return NOTHING;


}


CellInfo* MapIndex::getCell(int x,int y)
{
	/*if(x<themap->getWidth() && y<themap->getHeight() && x>=0 && y>=0)
	  return informationgrid[x][y];*/
	if(informationgrid.find(pair<int,int>(x,y))!=informationgrid.end())
	{
		return informationgrid[pair<int,int>(x,y)];
	}
	else
		return NULL;
}


bool MapIndex::AddCharacter(BaseCharacter* bchar)
{

	int x=bchar->getPosition().y/themap->getTileSize();
	int y=bchar->getPosition().x/themap->getTileSize();

	if(themap->getCollisionTiles()[y][x]->getID()!=1)
	{
		//informationgrid[x][y]=new CellInfo(bchar->getID(),CHARACTER_T);
		informationgrid[pair<int,int>(x,y)]=new CellInfo(bchar->getID(),CHARACTER_T);
		themap->Set(y,x,2,LCOLISION);
		return true;
	}
	cout<<"Failed to add the character"<<endl;
	return false;



}

bool MapIndex::AddItem(Item *it)
{
	int x=it->getPosition().y/themap->getTileSize();
	int y=it->getPosition().x/themap->getTileSize();

	if(themap->getCollisionTiles()[y][x]->getID()!=1)
	{
		//informationgrid[x][y]=new CellInfo(it->getID(),OBJECT_T);
		informationgrid[pair<int,int>(x,y)]=new CellInfo(it->getID(),OBJECT_T);
		themap->Set(y,x,2,LCOLISION);
		return true;
	}

	return false;
}

bool MapIndex::AddDoodad(Doodad *doodad)
{
	int x=doodad->GetEntity()->getPosition().y/themap->getTileSize();
	int y=doodad->GetEntity()->getPosition().x/themap->getTileSize();
	doodad->SetID(doodads.size());
	doodads[doodad->GetID()]=doodad;
  
	if(themap->getCollisionTiles()[y][x]->getID()!=1  && themap->getCollisionTiles()[y][x]->getID()!=2)
	{
		//informationgrid[x][y]=new CellInfo(doodad->GetID(),DOODAD_T);
		informationgrid[pair<int,int>(x,y)]=new CellInfo(doodad->GetID(),DOODAD_T); 
		//Assuming all doodads block vision by default
		themap->Set(y,x,doodad->getVisibility(),LCOLISION);
		return true;
	}

	return false;
}

Doodad* MapIndex::getDoodad(unsigned int id)
{
	std::unordered_map<unsigned int,Doodad*>::iterator it;
	it=doodads.find(id);
	if(it==doodads.end())
	{
		return NULL;
	}

	else
	{
		return it->second;
	}
}

std::unordered_map<unsigned int,Doodad*>& MapIndex::getDoodads()
{
	return this->doodads;
}

bool MapIndex::RemoveItem(unsigned int id)
{
  
	Item *item=KnowledgePool::Instance()->getItem(id);
	if(item!=NULL)
	{
		int x=item->getPosition().y/TILE_SIZE;
		int y=item->getPosition().x/TILE_SIZE;
		//informationgrid[x][y]=NULL;
      
		informationgrid.erase(pair<int,int>(x,y));
		themap->Set(y,x,0,LCOLISION);
	}
	return true;
}

bool MapIndex::RemoveDoodad(unsigned int id)
{
	Doodad *doodad=getDoodad(id);
	if(doodad!=NULL)
	{
		int x=doodad->GetEntity()->getPosition().y/TILE_SIZE;
		int y=doodad->GetEntity()->getPosition().x/TILE_SIZE;
		//informationgrid[x][y]=NULL;
		informationgrid.erase(pair<int,int>(x,y));
		themap->Set(y,x,0,LCOLISION);
	}
	return true;
}

bool MapIndex::ItemIndexUpdate(Item *item,int xpos,int ypos)
{

	/*
	  for(int i=0; i<informationgrid.size(); i++)
	  {
	  for(int j=0; j<informationgrid.size(); j++)
	  {
	  if(informationgrid[i][j]!=NULL)
	  {
	  if( informationgrid[i][j]->getType()==OBJECT_T  && informationgrid[i][j]->getID()==item->getID()  )
	  {
	  int x=(item->getPosition().y+ypos)/themap->getTileSize();
	  int y=(item->getPosition().x+xpos)/themap->getTileSize();
	  if(themap->getCollisionTiles()[x][y]->getID()==0)
	  {
	  themap->Set(j,i,0,LCOLISION);
	  delete informationgrid[i][j];
	  informationgrid[i][j]=NULL;

	  informationgrid[x][y]=new CellInfo(item->getID(),OBJECT_T);
	  //std::cout<<":registering new tileinfo and collision:: "<<y<<','<<x<<std::endl;
	  themap->Set(y,x,2,LCOLISION);
	  SDL_Rect vis;
	  vis.x=y*TILE_SIZE;
	  vis.y=x*TILE_SIZE;
	  //ComputeVision(vis);
	  return true;
	  }
	  }

	  }
	  }
  
	  }*/
	unordered_map<pair<int,int>,CellInfo*,mapindex_hash>::iterator it;
	for(it=informationgrid.begin();it!=informationgrid.end();++it)
	{
		if(it->second->getType()==OBJECT_T && it->second->getID()==item->getID())
		{
			int x=(item->getPosition().y+ypos)/themap->getTileSize();
			int y=(item->getPosition().x+xpos)/themap->getTileSize();
			if(themap->getCollisionTiles()[x][y]->getID()==0)
			{
				themap->Set(it->first.second,it->first.first,0,LCOLISION);
				delete it->second;
				informationgrid.erase(it->first);
				//delete informationgrid[i][j];
				//informationgrid[i][j]=NULL;
	      
				//informationgrid[x][y]=new CellInfo(item->getID(),OBJECT_T);
				informationgrid[pair<int,int>(x,y)]=new CellInfo(item->getID(),OBJECT_T);
				themap->Set(y,x,2,LCOLISION);
	      
				return true;
			}
		}
	}
	return false;
}

bool MapIndex::CharIndexUpdate(BaseCharacter *selected,int xpos,int ypos)
{
	/*
	  for(int i=0; i<informationgrid.size(); i++)
	  {
	  for(int j=0; j<informationgrid.size(); j++)
	  {
	  if(informationgrid[i][j]!=NULL)
	  {
	  if( informationgrid[i][j]->getType()==CHARACTER_T && informationgrid[i][j]->getID()==selected->getID() )
	  {
	  int x=(selected->getPosition().y+ypos)/themap->getTileSize();
	  int y=(selected->getPosition().x+xpos)/themap->getTileSize();
	  if(themap->getCollisionTiles()[x][y]->getID()==0)
	  {
	  themap->Set(j,i,0,LCOLISION);
	  delete informationgrid[i][j];
	  informationgrid[i][j]=NULL;

	  informationgrid[x][y]=new CellInfo(selected->getID(),CHARACTER_T);
	  //std::cout<<":registering new tileinfo and collision:: "<<y<<','<<x<<std::endl;
	  themap->Set(y,x,2,LCOLISION);
	  SDL_Rect vis;
	  vis.x=y*TILE_SIZE;
	  vis.y=x*TILE_SIZE;
	  //ComputeVision(vis);
	  return true;
	  }
	  }

	  }
	  }
	  }*/

	unordered_map<pair<int,int>,CellInfo*,mapindex_hash>::iterator it;
	for(it=informationgrid.begin();it!=informationgrid.end();++it)
	{
		if(it->second->getType()==CHARACTER_T && it->second->getID()==selected->getID())
		{
			int x=(selected->getPosition().y+ypos)/themap->getTileSize();
			int y=(selected->getPosition().x+xpos)/themap->getTileSize();
			if(themap->getCollisionTiles()[x][y]->getID()==0)
			{
				themap->Set(it->first.second,it->first.first,0,LCOLISION);
				delete it->second;
				informationgrid.erase(it->first);
				//delete informationgrid[i][j];
				//informationgrid[i][j]=NULL;
	      
				//informationgrid[x][y]=new CellInfo(item->getID(),OBJECT_T);
				informationgrid[pair<int,int>(x,y)]=new CellInfo(selected->getID(),CHARACTER_T);
				themap->Set(y,x,2,LCOLISION);
	      
				return true;
			}
		}
	}
	return false;

}

bool MapIndex::DoodadIndexUpdate(Doodad *doodad,int xpos,int ypos,int visibility)
{

	/*
	  for(int i=0; i<informationgrid.size(); i++)
	  {
	  for(int j=0; j<informationgrid.size(); j++)
	  {
	  if(informationgrid[i][j]!=NULL)
	  {
	  if( informationgrid[i][j]->getType()==DOODAD_T  && informationgrid[i][j]->getID()==doodad->GetID()  )
	  {
	  int x=(doodad->GetEntity()->getPosition().y+ypos)/themap->getTileSize();
	  int y=(doodad->GetEntity()->getPosition().x+xpos)/themap->getTileSize();
	  if(themap->getCollisionTiles()[x][y]->getID()==0)
	  {
	  themap->Set(j,i,0,LCOLISION);
	  delete informationgrid[i][j];
	  informationgrid[i][j]=NULL;

	  informationgrid[x][y]=new CellInfo(doodad->GetID(),DOODAD_T);
	  //std::cout<<":registering new tileinfo and collision:: "<<y<<','<<x<<std::endl;
	  themap->Set(y,x,1,LCOLISION);
	  SDL_Rect vis;
	  vis.x=y*TILE_SIZE;
	  vis.y=x*TILE_SIZE;
	  //ComputeVision(vis);
	  return true;
	  }
	  }

	  }
	  }
  
	  }*/
	unordered_map<pair<int,int>,CellInfo*,mapindex_hash>::iterator it;
	for(it=informationgrid.begin();it!=informationgrid.end();++it)
	{
		if(it->second->getType()==DOODAD_T && it->second->getID()==doodad->GetID())
		{
			int x=(doodad->GetEntity()->getPosition().y+ypos)/themap->getTileSize();
			int y=(doodad->GetEntity()->getPosition().x+xpos)/themap->getTileSize();
			if(themap->getCollisionTiles()[x][y]->getID()==0)
			{
				themap->Set(it->first.second,it->first.first,0,LCOLISION);
				delete it->second;
				informationgrid.erase(it->first);
				//delete informationgrid[i][j];
				//informationgrid[i][j]=NULL;
	      
				//informationgrid[x][y]=new CellInfo(item->getID(),OBJECT_T);
				informationgrid[pair<int,int>(x,y)]=new CellInfo(doodad->GetID(),DOODAD_T);
				themap->Set(y,x,visibility,LCOLISION);
	      
				return true;
			}
		}
	}
	return false;
}

bool MapIndex::RectCollides(SDL_Rect big,SDL_Rect small)
{

	if(small.x>big.x+big.w)
		return false;
	else if(small.y+small.h<big.y)
		return false;
	else if(small.x+small.w<big.x)
		return false;
	if(small.y>big.y+big.h)
		return false;
	return true;

}



bool  MapIndex::Mark(int y,int x)
{

	visibilityvector[x][y]=true;
	if(themap->getCollisionTiles()[y][x]->getID()==0 || themap->getCollisionTiles()[y][x]->getID()==2 )
		return true;
	return false;

}

bool  MapIndex::RayTest(int y,int x)
{

	if(themap->getCollisionTiles()[y][x]->getID()==0  || themap->getCollisionTiles()[y][x]->getID()==2 )
		return true;
	return false;

}

bool MapIndex::RayTrace(int x0, int y0, int x1, int y1)
{
	int dx = abs(x1 - x0);
	int dy = abs(y1 - y0);
	int x = x0;
	int y = y0;
	int n = 1 + dx + dy;
	int x_inc = (x1 > x0) ? 1 : -1;
	int y_inc = (y1 > y0) ? 1 : -1;
	int error = dx - dy;
	dx *= 2;
	dy *= 2;

	for (; n > 0; --n)
	{
		if(! RayTest(x, y))
			return false;

		if (error > 0)
		{
			x += x_inc;
			error -= dy;
		}
		else
		{
			y += y_inc;
			error += dx;
		}
	}
	return true;
}

bool MapIndex::MarkPath(int x0, int y0, int x1, int y1)
{
	int dx = abs(x1 - x0);
	int dy = abs(y1 - y0);
	int x = x0;
	int y = y0;
	int n = 1 + dx + dy;
	int x_inc = (x1 > x0) ? 1 : -1;
	int y_inc = (y1 > y0) ? 1 : -1;
	int error = dx - dy;
	dx *= 2;
	dy *= 2;

	for (; n > 0; --n)
	{
		if(! Mark(x, y))
			return false;

		if (error >= 0)
		{
			x += x_inc;
			error -= dy;
		}
		else
		{
			y += y_inc;
			error += dx;
		}
	}
	return true;
}

void MapIndex::ComputeVision(SDL_Rect center)
{
  
	
	//Actually limit to camera bounds ?
	for(int i=0; i<visibilityvector.size(); i++)
		for(int j=0; j<visibilityvector.size(); j++)
		{

			visibilityvector[i][j]=false;
		}


  
  
	//from center-visibility to center+visibility
  
	for(int i=0;i<themap->getWidth();i++)
	{
		if(MarkPath(center.y/TILE_SIZE,center.x/TILE_SIZE,0,i))
		{
			visibilityvector[i][0]=true;
		}
		if(MarkPath(center.y/TILE_SIZE,center.x/TILE_SIZE,themap->getHeight()-1,i))
		{
			visibilityvector[i][themap->getHeight()-1]=true;
		}
	}

	for(int i=0;i<themap->getHeight();i++)
	{
		if(MarkPath(center.y/TILE_SIZE,center.x/TILE_SIZE,i,0))
		{
			visibilityvector[0][i]=true;
		}

		if(MarkPath(center.y/TILE_SIZE,center.x/TILE_SIZE,i,themap->getWidth()-1))
		{
			visibilityvector[themap->getWidth()-1][i]=true;
		}
	}
	
	for(int i=0; i<visibilityvector.size(); i++)
	{
		for(int j=0; j<visibilityvector.size(); j++)
		{
			if(center.y/TILE_SIZE < j)
			{
				if(visibilityvector[i][j-1] && !VisionBlocking(j-1,i))
				{
					//visioncorrection[i][j]=true;
					visibilityvector[i][j]=true;
				}
		      
			}
			else if(center.y/TILE_SIZE > j)
			{
				if(visibilityvector[i][j+1] && !VisionBlocking(j+1,i))
				{
					//visioncorrection[i][j]=true;
					visibilityvector[i][j]=true;
				}
			}

			if(center.x/TILE_SIZE < i)
			{
				if(visibilityvector[i-1][j] && !VisionBlocking(j,i-1))
				{
					//visioncorrection[i][j]=true;
					visibilityvector[i][j]=true;
				}
			}
			else if(center.x/TILE_SIZE > i)
			{
				if(visibilityvector[i+1][j]  && !VisionBlocking(j,i+1))
				{
					//visioncorrection[i][j]=true;
					visibilityvector[i][j]=true;
				}
			}
		}
		
	}
	vector<vector<bool>> copy=visibilityvector;
	for(int i=0; i<visibilityvector.size(); i++)
	{
		for(int j=0; j<visibilityvector.size(); j++)
		{
			if(!copy[i][j] && VisionBlocking(j,i))
			{
				if(VisionBlocking(j+1,i) && VisionBlocking(j,i+1))
				{
					if(copy[i][j+1] && copy[i+1][j])
					{
						visibilityvector[i][j]=true;
					}
				}
				if(VisionBlocking(j+1,i) && VisionBlocking(j,i-1))
				{
					if(copy[i][j+1] && copy[i-1][j])
					{
						visibilityvector[i][j]=true;
					}
				}
			
				if(VisionBlocking(j-1,i) && VisionBlocking(j,i+1))
				{
					if(copy[i][j-1] && copy[i+1][j])
					{
						visibilityvector[i][j]=true;
					}
				}

				if(VisionBlocking(j-1,i) && VisionBlocking(j,i-1))
				{
					if(copy[i][j-1] && copy[i-1][j])
					{
						visibilityvector[i][j]=true;
					}
				}
			}
		}
		
	}
	/*
	  for(int k=0;k<Walls.size();k++)
	  {
	  int i=Walls[k].first;
	  int j=Walls[k].second;
      
	  if(IsWall(j,i-1) && IsWall(j,i+1))
	  {
	  //camera is above
	  if(center.y/TILE_SIZE < j)
	  {
	  if(visibilityvector[i][j-1])
	  visibilityvector[i][j]=true;
	  }
	  else
	  {
	  if(visibilityvector[i][j+1])
	  visibilityvector[i][j]=true;
	  }
	  }
/*
if( (center.x/TILE_SIZE)>i && (center.y/TILE_SIZE)>j)
{
if ( (visibilityvector[i+1][j] && !IsWall(j,i+1) ) || (visibilityvector[i][j+1] && !IsWall(j+1,i)  )|| ( visibilityvector[i+1][j+1]) && !IsWall(j+1,i+1)  )
visibilityvector[i][j]=true;
}
else  if( (center.x/TILE_SIZE)<i && (center.y/TILE_SIZE)>j)
{

if( (visibilityvector[i-1][j] && !IsWall(j,i-1)) || (visibilityvector[i][j+1] && !IsWall(j+1,i)) || (visibilityvector[i-1][j+1] && !IsWall(j+1,i-1)) )
visibilityvector[i][j]=true;
}
else  if( (center.x/TILE_SIZE)>i && (center.y/TILE_SIZE)<j)
{
if( ( visibilityvector[i+1][j-1]  && !IsWall(j-1,i+1)) || ( visibilityvector[i+1][j] && !IsWall(j,i+1) ) || ( visibilityvector[i][j-1]  && !IsWall(j-1,i) ) )
visibilityvector[i][j]=true;
}

else if( (center.x/TILE_SIZE)<i && (center.y/TILE_SIZE)<j)
{
if(  (visibilityvector[i-1][j] && !IsWall(j,i-1) ) ||  (visibilityvector[i][j-1]  && !IsWall(j-1,i) ) ||( visibilityvector[i-1][j-1]  && !IsWall(j-1,i-1) ) )
visibilityvector[i][j]=true;
}
	*/
			      // }

			      unordered_map<unsigned int,Doodad*>::iterator dood_it;
			      for(dood_it=doodads.begin();dood_it!=doodads.end();++dood_it)
			      {
				      int i=dood_it->second->GetEntity()->getPosition().x/TILE_SIZE;
				      int j=dood_it->second->GetEntity()->getPosition().y/TILE_SIZE;
	  
				      if( (center.x/TILE_SIZE)>i && (center.y/TILE_SIZE)>j)
				      {
					      if ( (visibilityvector[i+1][j] && !IsWall(j,i+1) ) || (visibilityvector[i][j+1] && !IsWall(j+1,i)  )|| ( visibilityvector[i+1][j+1]) && !IsWall(j+1,i+1)  )
						      visibilityvector[i][j]=true;
				      }
				      else  if( (center.x/TILE_SIZE)<i && (center.y/TILE_SIZE)>j)
				      {

					      if( (visibilityvector[i-1][j] && !IsWall(j,i-1)) || (visibilityvector[i][j+1] && !IsWall(j+1,i)) || (visibilityvector[i-1][j+1] && !IsWall(j+1,i-1)) )
						      visibilityvector[i][j]=true;
				      }
				      else  if( (center.x/TILE_SIZE)>i && (center.y/TILE_SIZE)<j)
				      {
					      if( ( visibilityvector[i+1][j-1]  && !IsWall(j-1,i+1)) || ( visibilityvector[i+1][j] && !IsWall(j,i+1) ) || ( visibilityvector[i][j-1]  && !IsWall(j-1,i) ) )
						      visibilityvector[i][j]=true;
				      }

				      else if( (center.x/TILE_SIZE)<i && (center.y/TILE_SIZE)<j)
				      {
					      if(  (visibilityvector[i-1][j] && !IsWall(j,i-1) ) ||  (visibilityvector[i][j-1]  && !IsWall(j-1,i) ) ||( visibilityvector[i-1][j-1]  && !IsWall(j-1,i-1) ) )
						      visibilityvector[i][j]=true;
				      }
			      }
  

}

bool MapIndex::VisionBlocking(int x,int y)
{
	if( themap->getCollisionTiles()[x][y]->getID()==1  /*&& themap->getCollisionTiles()[x][y]->getID()!=2)*/  /*&& !informationgrid[y][x]*/)
	{
		return true;
	}

	return false;
}

bool MapIndex::IsWall(int x,int y)
{

	if(VisionBlocking(x,y))
	{
		if(x-1>=0 && x+1<themap->getWidth())
		{
			if(VisionBlocking(x-1,y) && VisionBlocking(x+1,y))//Between walls x-1 x+1
			{
				return true;
			}
		}
		if(y-1>=0 && y+1<themap->getHeight())
		{
			if(VisionBlocking(x,y-1) && VisionBlocking(x,y-1))//Between walls y-1 y+1
			{
				return true;
			}
		}

		if(x+1<themap->getWidth() && y-1>=0)
		{
			if(VisionBlocking(x+1,y) && VisionBlocking(x,y-1))//Between walls x+1 y-1
			{
				return true;
			}
		}


		if(x+1<themap->getWidth() && y<themap->getHeight())
		{
			if(VisionBlocking(x+1,y) && VisionBlocking(x,y+1))//Between walls x+1 y+1
			{
				return true;
			}
		}

		if( x-1>=0 && y+1<themap->getHeight())
		{
			if(VisionBlocking(x-1,y) && VisionBlocking(x,y+1))//Between walls x-1 y+1
			{
				return true;
			}
		}

		if( x-1>=0 && y-1>=0)
		{
			if(VisionBlocking(x-1,y) && VisionBlocking(x,y-1))//Between walls y-1 y-1
			{
				return true;
			}

		}
	}

	return false;



}




bool MapIndex::getVisible(int x,int y)
{
	if(x>=0 && y>=0 && x<themap->getWidth() && y<themap->getHeight())
		return this->visibilityvector[y][x];
	return false;
}



Map* MapIndex::getMap()
{
	return themap;
}




bool MapIndex::IsPathable(int x,int y)
{
	if(x>=0 && y>=0 && x<themap->getWidth() && y<themap->getHeight())
		if(themap->getCollisionTiles()[x][y]->getID()==0)
		{
			return true;
		}

	return false;

}

bool MapIndex::IsVisible(int x,int y)
{
	if(x>=0 && y>=0 && x<themap->getWidth() && y<themap->getHeight())
		if(themap->getCollisionTiles()[x][y]->getID()==0 || themap->getCollisionTiles()[x][y]->getID()==2)
		{
			return true;
		}

	return false;

}



vector<CellInfo*> MapIndex::getEntitiesInRange(int xpos,int ypos,int radius)
{
	//Bruteforce but effective for now //Can be optimized to run in a single loop
	vector<CellInfo*> entities;
	for(int y=-radius; y<=radius; y++)
		for(int x=-radius; x<=radius; x++)
			if(x*x+y*y <= radius*radius)
				if(getCell(xpos+x, ypos+y))
				{
					entities.push_back(getCell(xpos+x,ypos+y));
				}
	return entities;
}

vector<CellInfo*>     MapIndex::getEntitiesInLine(int xpos,int ypos,int width,DIRECTION dir)
{
	vector<CellInfo*> entities;
	for(int i=0;i<width;i++)
	{
		switch (dir)
		{
		case LEFT:
			if(getCell(xpos,ypos-i))
				entities.push_back(getCell(xpos,ypos-i));
			break;
		case RIGHT:
			if(getCell(xpos,ypos+i))
				entities.push_back(getCell(xpos,ypos+i));
			break;
		case UP:
			if(getCell(xpos-i,ypos))
				entities.push_back(getCell(xpos-i,ypos));
			break;
		case DOWN:
			if(getCell(xpos+i,ypos))
				entities.push_back(getCell(xpos+i,ypos));
			break;
		}
	}
	return entities;
}

vector<pair<int,int>> MapIndex::getTilesInRange(int xpos,int ypos,int radius,bool include_entities)
{
	vector<pair<int,int>> tiles;
  
	for(int y=-radius; y<=radius; y++)
		for(int x=-radius; x<=radius; x++)
			if(Distances::Manhattan_Distance(pair<int,int>(xpos,ypos),pair<int,int>(xpos+x,ypos+y))<=radius/*x*x+y*y <= radius*radius*/)
			{
				if(getVisible(ypos+y,xpos+x))
				{
					if(IsPathable(ypos+y,xpos+x))
					{
						tiles.push_back(pair<int,int>(ypos+y,xpos+x));
					}
					if(include_entities && getCell(ypos+y,xpos+x))
					{
						tiles.push_back(pair<int,int>(ypos+y,xpos+x));
					}
				}
			}
	return tiles;
  
}
