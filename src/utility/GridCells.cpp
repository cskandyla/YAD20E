#include "CellInfo.h"
#include "MapIndex.h"
#include "GridCells.h"

GridCells::GridCells(int xpos,int ypos,int radius,int alpha)
{

  
  for(int y=-radius; y<radius; y++)
    for(int x=-radius; x<radius; x++)
        if(x*x+y*y <= radius*radius)
	  {
	    SDL_Surface *surf=SDL_CreateRGBSurface(0,MapIndex::Instance()->getMap()->getTileSize(),MapIndex::Instance()->getMap()->getTileSize(),32,00,00,00,00);
	    SDL_Rect r{(short)((xpos+x)*MapIndex::Instance()->getMap()->getTileSize()),(short)((ypos+y)*MapIndex::Instance()->getMap()->getTileSize()),
		(unsigned short)(MapIndex::Instance()->getMap()->getTileSize()),(unsigned short)(MapIndex::Instance()->getMap()->getTileSize())};

	      grid_cells.push_back(pair<SDL_Rect,SDL_Surface*>(r,surf));
	    if(MapIndex::Instance()->getCell(xpos+x, ypos+y))
	    {
	      SDL_FillRect(surf, NULL, 0x00FF00);
	      
	    }
	    else
	      {
		SDL_FillRect(surf, NULL, 0x0000FF);
	      }
	    SDL_SetSurfaceAlphaMod(surf,alpha);
	  }
  
}


void GridCells::Draw(SDL_Surface *screen)
{

  for(int i=0;i<grid_cells.size();i++)
    {
      SDL_BlitSurface(grid_cells[i].second,NULL,screen,&grid_cells[i].first);
    }

}

 
GridCells::~GridCells()
{

    for(int i=0;i<grid_cells.size();i++)
    {
            SDL_FreeSurface(grid_cells[i].second);
    }

}
 
