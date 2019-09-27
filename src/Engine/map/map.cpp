#include "map.h"
#include <fstream>
#include <string>
#include <iostream>
#include <cstring>
#include "pugixml.hpp"
#include "Tokenizer.h"
#include "miscellaneous.h"
#include <dirent.h>
#include "params.h"
#include "BaseRenderer.h"
using namespace pugi;
using std::ofstream;
using std::ifstream;
using std::ios;
using std::string;
Map::Map(int tilesize)
{
  this->tilesize=tilesize;
  this->toshow=SALL;
  lastid=0;
  this->width=0;
  this->height=0;
  showtriggers=false;
}

Map::~Map()
{
  for(int i=0;i<groundtiles.size();i++)
    {
      for(int j=0;j<groundtiles[i].size();j++)
	if(groundtiles[i][j])
	  delete groundtiles[i][j];
    }
  for(int i=0;i<objecttiles.size();i++)
    {
      for(int j=0;j<objecttiles[i].size();j++)
	if(objecttiles[i][j])
	  delete objecttiles[i][j];
    }
  for(int i=0;i<CollisionTiles.size();i++)
    {
      for(int j=0;j<CollisionTiles[i].size();j++)
	if(CollisionTiles[i][j])
	  delete CollisionTiles[i][j];
    }

  unordered_map<int,pair<string,SDL_Texture*>>::iterator it;
  for(it=groundsurfaces.begin();it!=groundsurfaces.end();++it)
    {
      SDL_DestroyTexture(it->second.second);
    }
  for(it=objectsurfaces.begin();it!=objectsurfaces.end();++it)
    {
      SDL_DestroyTexture(it->second.second);
    }
  for(it=ColisionSurfaces.begin();it!=ColisionSurfaces.end();++it)
    {
      SDL_DestroyTexture(it->second.second);
    }
		  
  for(int i=0;i<Triggers.size();i++)
    delete Triggers[i];
}


void Map::Show(SDL_Texture *screen)
{
  SDL_Rect pos;
  pos.x=0;
  pos.y=0;
  pos.w=tilesize;
  pos.h=tilesize;
  for(int i=0; i<groundtiles.size(); i++)
    for(int j=0; j<groundtiles[i].size(); j++)
      {
	pos.x=i*tilesize;
	pos.y=j*tilesize;

	if(groundtiles[j][i]->getID()!=-1 &&  (toshow==SALL || toshow==SGROUND || toshow==SVISIBLE) )
	  {
	    //SDL_BlitSurface(groundsurfaces[groundtiles[j][i]->getID()].second,NULL,screen,&pos);
	    //SDL_RenderCopy(renderer,groundsurfaces[groundtiles[j][i]->getID()].second,NULL,&pos);
	    BaseRenderer::Instance()->RenderTexture(groundsurfaces[groundtiles[j][i]->getID()].second,screen,NULL,&pos);
	  }

	if(objecttiles[j][i]->getID()!=-1 && (toshow==SALL || toshow==SOBJECT || toshow==SVISIBLE) )
	  {
	    BaseRenderer::Instance()->RenderTexture(objectsurfaces[objecttiles[j][i]->getID()].second,screen,NULL,&pos);
	  }
	  //SDL_RenderCopy(renderer,objectsurfaces[objecttiles[j][i]->getID()].second,NULL,&pos);

	if(CollisionTiles[j][i]->getID()!=-1 && (toshow==SALL || toshow==SCOLISION) )
	  {
	    BaseRenderer::Instance()->RenderTexture(ColisionSurfaces[CollisionTiles[j][i]->getID()].second,screen,NULL,&pos);
	  }
	  // SDL_RenderCopy(renderer,ColisionSurfaces[CollisionTiles[j][i]->getID()].second,NULL,&pos);

      }



}

void Map::Set(int i,int j,int surfid,TILEMAP_LAYER t)
{
  //cout<<"i,j:"<<i<<','<<j<<endl;
  if(i>=0 && j>=0 && j<width && i<height)
    {

      if(t==LGROUND)
	groundtiles[j][i]->setID(surfid);
      else if(t==LOBJECT)
	objecttiles[j][i]->setID(surfid);
      else if(t==LCOLISION)
	CollisionTiles[j][i]->setID(surfid);
    }

}

void Map::AddSurface(string surf,TILEMAP_LAYER t)
{

  string buffer=surf;

  std::cout<<"ADDING"<<buffer<<std::endl;

  SDL_Texture *surface=loadTexture(buffer.c_str(),BaseRenderer::Instance()->Renderer());
  if(surface==NULL)
    {
      cout<<"Loading "<<buffer<<" failed"<<endl;
      return;
    }
  


  if(t==LGROUND)
    {
      //this->groundsurfaces.push_back(pair<string,SDL_Surface*>(buffer,surface));
      groundsurfaces[groundsurfaces.size()]=pair<string,SDL_Texture*>(buffer,surface);
    }
  else if(t==LOBJECT)
    {
      objectsurfaces[objectsurfaces.size()]=pair<string,SDL_Texture*>(buffer,surface);
    }
  else if(t==LCOLISION)
    {
      ColisionSurfaces[ColisionSurfaces.size()]=pair<string,SDL_Texture*>(buffer,surface);
    }
  std::cout<<"ADDED"<<buffer<<std::endl;


}

void Map::Fill(int surfid,TILEMAP_LAYER t)
{
  if(t==LGROUND)
    for(int i=0; i<groundtiles.size(); i++)
      for(int j=0; j<groundtiles[i].size(); j++)
	{
	  groundtiles[i][j]->setID(surfid);

	}
  else if(t==LOBJECT)
    for(int i=0; i<objecttiles.size(); i++)
      for(int j=0; j<objecttiles[i].size(); j++)
	{
	  objecttiles[i][j]->setID(surfid);

	}
  else if(t==LCOLISION)
    for(int i=0; i<CollisionTiles.size(); i++)
      for(int j=0; j<CollisionTiles[i].size(); j++)
	{
	  CollisionTiles[i][j]->setID(surfid);

	}
}

void Map::FillNew(int surfid,TILEMAP_LAYER t,int width,int height)
{

  this->width=width;
  this->height=height;
  groundtiles.resize(width);
  objecttiles.resize(width);
  CollisionTiles.resize(height);
  for(int i=0; i<width; i++)
    {
      groundtiles[i].resize(height);
      objecttiles[i].resize(height);
      CollisionTiles[i].resize(height);
    }

  for(int i=0; i<groundtiles.size(); i++)
    for(int j=0; j<groundtiles[i].size(); j++)
      {
	groundtiles[i][j]=new Tile(surfid);
	objecttiles[i][j]=new Tile(surfid);
	CollisionTiles[i][j]=new Tile(surfid);

      }


  /*
    if(t==LGROUND)
    for(int i=0; i<groundtiles.size(); i++)
    for(int j=0; j<groundtiles[i].size(); j++)
    {
    groundtiles[i][j]->setID(surfid);

    }
    else if(t==LOBJECT)
    for(int i=0; i<objecttiles.size(); i++)
    for(int j=0; j<objecttiles[i].size(); j++)
    {
    objecttiles[i][j]->setID(surfid);

    }
    else if(t==LCOLISION)
    for(int i=0; i<CollisionTiles.size(); i++)
    for(int j=0; j<CollisionTiles[i].size(); j++)
    {
    CollisionTiles[i][j]->setID(surfid);

    }*/
}


void Map::Save(char *file)
{
  ofstream out;
  out.open(file,ios::out);
  out<<"<Tiles>\n";
  out<<"<Ground>\n";
  for(int i=0; i<groundsurfaces.size(); i++)
    {
      out<<"<Tile>\n";
      out<<groundsurfaces[i].first<<"\n";
      out<<"</Tile>\n";
    }
  out<<"</Ground>\n";
  out<<"<Object>\n";
  for(int i=0; i<objectsurfaces.size(); i++)
    {
      out<<"<Tile>\n";
      out<<objectsurfaces[i].first<<"\n";
      out<<"</Tile>\n";
    }
  out<<"</Object>\n";
  out<<"</Tiles>\n";
  out<<"<MAP>\n";
  out<<"<Size>\n";
  out<<width<<","<<height<<"\n";
  out<<"</Size>\n";
  out<<"<GroundMap>\n";
  for(int i=0; i<groundtiles.size(); i++)
    {
      for(int j=0; j<groundtiles[i].size(); j++)
	out<<groundtiles[i][j]->getID()<<" ";
      out<<"\n";
    }
  out<<"</GroundMap>\n";
  out<<"<ObjectMap>\n";
  for(int i=0; i<objecttiles.size(); i++)
    {
      for(int j=0; j<objecttiles[i].size(); j++)
	out<<objecttiles[i][j]->getID()<<" ";
      out<<"\n";
    }
  out<<"</ObjectMap>\n";
  out<<"<ColisionMap>\n";
  for(int i=0; i<CollisionTiles.size(); i++)
    {
      for(int j=0; j<CollisionTiles[i].size(); j++)
	out<<CollisionTiles[i][j]->getID()<<" ";
      out<<"\n";
    }
  out<<"</ColisionMap>\n";
  out<<"<Triggers>\n";
  for(int i=0; i<Triggers.size(); i++)
    {
      out<<"<Trigger>\n";
      out<<"<CoordX>"<<Triggers[i]->getX()<<"</CoordX>\n";
      out<<"<CoordY>"<<Triggers[i]->getY()<<"</CoordY>\n";
      out<<"<Script>"<<Triggers[i]->getScript()<<"</Script>\n";
      out<<"</Trigger>\n";
    }
  out<<"</Triggers>\n";
  out<<"</MAP>\n";
  out.close();

}



void Map::Load(char *file)
{
  ifstream in;
  in.open(file);

  string s;
  getline(in,s);
  while(s.compare("</Tiles>")!=0)
    {
      if(s.c_str()[0]!='<')
	AddSurface((char*)s.c_str(),LGROUND);
      std::cout<<s<<std::endl;
      getline(in,s);

    }
  getline(in,s);
  getline(in,s);
  getline(in,s);
  char * pch;
  pch = strtok ((char*)s.c_str(),",");
  int width=atoi(pch);
  std::cout<<width<<std::endl;

  int height=atoi(pch);
  std::cout<<height<<std::endl;
  this->width=width;
  this->height=height;
  getline(in,s);
  getline(in,s);
  for(int i=0; i<width; i++)
    {
      getline(in,s);
      pch = strtok ((char*)s.c_str()," ");
      std::cout<<pch<<" ";
      groundtiles[i][0]=new Tile(atoi(pch));
      for(int j=0; j<height-1; j++)
        {
	  pch = strtok (NULL, " ");
	  groundtiles[i][j+1]=new Tile(atoi(pch));
	  std::cout<<pch<<" ";
        }
      std::cout<<std::endl;
    }
  in.close();
}

void Map::LoadProperly(char *file)
{
  Triggers.clear();
  xml_document doc;
  xml_parse_result result = doc.load_file(file);
  //Add the blank tile with an empty string for Ground and Object layers.
  // AddSurface("Resources/Tiles/Colision/blank.png",LGROUND);
  // AddSurface("Resources/Tiles/Colision/blank.png",LOBJECT);
  cout<<"LOADING GROUND TILES"<<endl;
  
  pugi::xml_node tools = doc.child("Tiles").child("Ground");
  for (pugi::xml_node tool = tools.child("Tile"); tool; tool = tool.next_sibling("Tile"))
    {

      string s=tool.first_child().value();
      s.erase(s.begin()+0);
      s.erase(s.end()-1);
      std::cout<<"found :"<<s;
      AddSurface((char*)s.c_str(),LGROUND);
    }
  cout<<"LOADING OBJECT TILES"<<endl;
  tools = doc.child("Tiles").child("Object");
  for (pugi::xml_node tool = tools.child("Tile"); tool; tool = tool.next_sibling("Tile"))
    {

      {
	string s=tool.first_child().value();
	s.erase(s.begin()+0);
	s.erase(s.end()-1);
	std::cout<<"found :"<<s;
	AddSurface((char*)s.c_str(),LOBJECT);
      }
    }
  
  AddSurface("Resources/Tiles/Colision/blank.png",LCOLISION);
  AddSurface("Resources/Tiles/Colision/colides.png",LCOLISION);
  AddSurface("Resources/Tiles/Colision/visible.png",LCOLISION);
  cout<<"LOADING SIZE "<<endl;
  tools = doc.child("MAP").child("Size");
  string s=tools.first_child().value();
  s.erase(s.begin()+0);
  s.erase(s.end()-1);
  std::cout<<"size"<<s;
  char * pch;
  pch = strtok ((char*)s.c_str(),",");
  int width=atoi(pch);
  std::cout<<width<<std::endl;

  int height=atoi(pch);
  std::cout<<height<<std::endl;
  this->width=width;
  this->height=height;
  groundtiles.resize(width);
  objecttiles.resize(width);
  CollisionTiles.resize(width);
  for(int i=0; i<width; i++)
    {
      groundtiles[i].resize(height);
      objecttiles[i].resize(height);
      CollisionTiles[i].resize(height);
    }

  for(int i=0; i<groundtiles.size(); i++)
    for(int j=0; j<groundtiles[i].size(); j++)
      {
	//	groundtiles[i][j]=new Tile(-1);
	//	objecttiles[i][j]=new Tile(-1);
	//	CollisionTiles[i][j]=new Tile(-1);
      }



  tools = doc.child("MAP").child("GroundMap");
  s=tools.first_child().value();
  s.erase(s.begin()+0);
  s.erase(s.end()-1);
  std::cout<<"map"<<s;

  Tokenizer t;
  t.setInput(s);
  cout<<"BOOM"<<endl;
  vector<string> tokens=t.split();
  int j=0,k=0;
  for(int i=0; i<tokens.size(); i++)
    if(i%(width)==0 && i!=0)
      {

	j=0;
	k++;
	cout<<"\n"<<tokens[i]<<" ";
	int l=atoi(tokens[i].c_str());

	groundtiles[k][j]=new Tile(l);


      }
    else if(i==0)
      {

	int l=atoi(tokens[i].c_str());
	groundtiles[k][j]=new Tile(l);
      }
    else
      {
	j++;
	cout<<tokens[i]<<" ";
	int l=atoi(tokens[i].c_str());

	groundtiles[k][j]=new Tile(l);

      }



  cout<<"MAP::"<<endl;
  for(int i=0; i<groundtiles.size(); i++)
    {
      for(int j=0; j<groundtiles[i].size(); j++)
	cout<<groundtiles[i][j]->getID()<<" ";
      cout<<"\n";
    }



  tools = doc.child("MAP").child("ObjectMap");
  s=tools.first_child().value();
  s.erase(s.begin()+0);
  s.erase(s.end()-1);
  std::cout<<"map"<<s;


  t.setInput(s);
  cout<<"BOOM"<<endl;
  tokens=t.split();
  j=0,k=0;
  for(int i=0; i<tokens.size(); i++)
    if(i%(width)==0 && i!=0)
      {

	j=0;
	k++;
	cout<<"\n"<<tokens[i]<<" ";
	int l=atoi(tokens[i].c_str());

	objecttiles[k][j]=new Tile(l);


      }
    else if(i==0)
      {

	int l=atoi(tokens[i].c_str());
	objecttiles[k][j]=new Tile(l);
      }
    else
      {
	j++;
	cout<<tokens[i]<<" ";
	int l=atoi(tokens[i].c_str());

	objecttiles[k][j]=new Tile(l);

      }


  cout<<"MAP::"<<endl;
  for(int i=0; i<objecttiles.size(); i++)
    {
      for(int j=0; j<objecttiles[i].size(); j++)
	cout<<objecttiles[i][j]->getID()<<" ";
      cout<<"\n";
    }




  tools = doc.child("MAP").child("ColisionMap");
  if(!tools.empty())
    {
      s=tools.first_child().value();
      s.erase(s.begin()+0);
      s.erase(s.end()-1);
      std::cout<<"map"<<s;


      t.setInput(s);
      cout<<"BOOM"<<endl;
      tokens=t.split();
      j=0,k=0;
      for(int i=0; i<tokens.size(); i++)
	if(i%(width)==0 && i!=0)
	  {

	    j=0;
	    k++;
	    cout<<"\n"<<tokens[i]<<" ";
	    int l=atoi(tokens[i].c_str());

	    CollisionTiles[k][j]=new Tile(l);


	  }
	else if(i==0)
	  {

	    int l=atoi(tokens[i].c_str());
	    CollisionTiles[k][j]=new Tile(l);
	  }
	else
	  {
	    j++;
	    cout<<tokens[i]<<" ";
	    int l=atoi(tokens[i].c_str());

	    CollisionTiles[k][j]=new Tile(l);

	  }
    }
  cout<<"\nTRIGGERS\n";
  tools = doc.child("MAP").child("Triggers");
  cout<<tools.value()<<'\n';
  for (pugi::xml_node tool = tools.child("Trigger"); tool; tool = tool.next_sibling("Trigger"))
    {


      int x=atoi(tool.child("CoordX").first_child().value());
      int y=atoi(tool.child("CoordY").first_child().value());
      string script=tool.child("Script").first_child().value();

      Triggers.push_back(new Trigger(x,y,script));
      cout<<"TRIGGER "<<x<<','<<y<<','<<script<<"\n";

    }

}



void Map::SetVisibleLayer(TILEMAP_SHOW t)
{
  this->toshow=t;
}


void Map::LoadTilesFromDirectory(string dir,TILEMAP_LAYER t)
{
  vector<string> surfnames;
  string  tempdir=dir;
  // first off, we need to create a pointer to a directory
  DIR *pdir = NULL; // remember, it's good practice to initialise a pointer to NULL!
  pdir = opendir (dir.c_str()); // "." will refer to the current directory
  struct dirent *pent = NULL;
  if (pdir == NULL) // if pdir wasn't initialised correctly
    {
      // print an error message and exit the program
      printf ("\nERROR! pdir could not be initialised correctly");
      return; // exit the function
    } // end if

  while (pent = readdir (pdir)) // while there is still something in the directory to list
    {
      if (pent == NULL) // if pent has not been initialised correctly
        {
	  // print an error message, and exit the program
	  printf ("\nERROR! pent could not be initialised correctly");
	  return; // exit the function
        }
      // otherwise, it was initialised correctly. let's print it on the console:
      printf ("%s\n", pent->d_name);
      if( strlen(pent->d_name)>3)
        {
	  /*if( pent->d_name[pent->d_namlen]=='t' && pent->d_name[pent->d_namlen-1]=='x'
	    && pent->d_name[pent->d_namlen-2]=='t'  && pent->d_name[pent->d_namlen-3]=='.')*/
	  tempdir+="\\";
	  string fname=tempdir+=pent->d_name;

	  AddSurface((char*)fname.c_str(),t);
	  tempdir=dir;
        }
    }

  // finally, let's close the directory
  closedir (pdir);



}


Tile* Map::getTile(int x,int y,TILEMAP_LAYER tl)
{
  if(tl==LGROUND)
    {
      return groundtiles[x][y];
    }
  else if(tl==LOBJECT)
    {
      return  objecttiles[x][y];
    }
  else if(tl==LCOLISION)
    {
      return CollisionTiles[x][y];
    }

  return NULL;
}


void Map::AddTrigger(Trigger *t)
{
  Triggers.push_back(t);

}


SDL_Texture* Map::GetSurface(int x,int y,TILEMAP_LAYER tl)
{

  if(tl==LGROUND)
    {
      return groundsurfaces[groundtiles[x][y]->getID()].second;
    }
  else if(tl==LOBJECT)
    {
      return objectsurfaces[objecttiles[x][y]->getID()].second;
    }
  else if(tl==LCOLISION)
    {
      return ColisionSurfaces[CollisionTiles[x][y]->getID()].second;
    }

  return NULL;

}
