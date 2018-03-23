#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>
#include <sstream>
#include <iostream>
#include <sstream>
#include <deque>
#include <cmath>
#include <vector>
#include <cstdlib>
#include <ctime>
#include "Game.h"
#include "ScriptHandler.h"
#include "ScriptConsole.h"
#include "OptionsMenu.h"
#include "MapIndex.h"
#include "Tokenizer.h"
#include "VisibleItem.h"
#include "Projectile.h"
#include "XmlBuilder.h"
#include "Renderer.h"
#include "TurnEngine.h"
#include "Astar.h"
#include "Seeker.h"
#include "miscellaneous.h"
#include "Colision.h"
#include "GameEngine.h"
#include  "params.h"
#include "ButtonMenu.h"
#include "SpellEffects.h"
#include "Camera.h"
#include "Lua_Export.h"
#include <lua.hpp>
#include "Label.h"
#include "BaseRenderer.h"
#include "Doodad.h"

#define M_PI 3.14159265358979323846
#include "Bars.h"
#include "SpellList.h"
//#include "CharacterSheet.h"
#include "UI.h"
#include "SpellInterface.h"

using std::cout;
using std::stringstream;
using std::deque;
using std::vector;



void LuaHandler(const char *s,Game *g)
{
  luaL_dostring(g->lua_state,s);
}

int main ( int argc, char* argv[] )
{
 
  // initialize SDL video
  if ( SDL_Init( SDL_INIT_VIDEO ) < 0 )
    {
      printf( "Unable to init SDL: %s\n", SDL_GetError() );
      return 1;
    }

  // make sure SDL cleans up before exit
  atexit(SDL_Quit);
  srand(time(NULL));

  // create a new window
  //INITIALIZATION
  //SDL_WM_SetCaption("YAD20E", "YAD20E");
  //SDL_Surface* screen = SDL_SetVideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, 32,
  //					 SDL_HWSURFACE|SDL_DOUBLEBUF/*|SDL_FULLSCREEN*/);
  SDL_Window *window=NULL;
  SDL_Surface *screen=NULL;
  window=SDL_CreateWindow("YAD20E",SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, 0  /*SDL_WINDOW_FULLSCREEN_DESKTOP */  );

  if(window==NULL)
    {
      printf("Couldnt Create Window");
    }
  else
    {
      screen=SDL_GetWindowSurface(window);
    }
  
  if ( !screen )
    {
      printf("Unable to set :%d,%d video: %s\n",SCREEN_WIDTH,SCREEN_HEIGHT, SDL_GetError());
      return 1;
    }
  SDL_Renderer *renderer=NULL;
  renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED|SDL_RENDERER_TARGETTEXTURE);
  if(!renderer)
    {
      printf("Failed to create renderer\n");
      return -1;
    }
  SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
  BaseRenderer::Instance()->Init(renderer);
  XmlBuilder::renderer=renderer;
  /* SDL_Surface *cursor_surf=loadSurface("Resources/UI/Icons/sword_cursor.png");
 SDL_Cursor *cursor = SDL_CreateColorCursor(cursor_surf, 0, 0);
    if (!cursor) {
      printf("Could not create cursor\n");
      return -1;
    }
    SDL_SetCursor(cursor);*/

  
  TTF_Init();
  TTF_Font *f =TTF_OpenFont("Resources/Fonts/Alpha Romanie.ttf",24);
  TTF_Font *fsmall=TTF_OpenFont("Resources/Fonts/Alpha Romanie.ttf",14);
  TTF_Font *consolefont=TTF_OpenFont("Resources/Fonts/Alpha Romanie.ttf",20);
  TTF_Font *logfont=TTF_OpenFont("Resources/Fonts/Alpha Romanie.ttf",16);
  TTF_Font *movesfont=TTF_OpenFont("Resources/Fonts/Alpha Romanie.ttf",14);
  TTF_Font *black_magic_font =TTF_OpenFont("Resources/Fonts/black-magic.ttf",20);

  //SDL_mixer

  int flags=MIX_INIT_OGG|MIX_INIT_MOD;
  int initted=Mix_Init(flags);
  if(initted&flags != flags) {
    printf("Mix_Init: Failed to init required ogg and mod support!\n");
    printf("Mix_Init: %s\n", Mix_GetError());
    // handle error
  }
  Mix_Music *menu_theme;
  Mix_OpenAudio(22050,MIX_DEFAULT_FORMAT,2,4096);

  menu_theme = Mix_LoadMUS("Resources/SoundFX/menu_music.ogg");
  if(menu_theme ==NULL)
    cout<<"Unable to load Ogg file: "<<Mix_GetError()<<endl;

  // Mix_PlayMusic(menu_theme,-1);

  //SURFACES AND RECTS


  SDL_Rect main_surface_rect;
  main_surface_rect.x=0;
  main_surface_rect.y=0;
  main_surface_rect.w=SCREEN_WIDTH*0.75;
  main_surface_rect.h=SCREEN_HEIGHT*0.84;
  SDL_Texture *Main_Game_Surface=SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, main_surface_rect.w,main_surface_rect.h);
  SDL_Rect toolbox_surface_rect;
  toolbox_surface_rect.x=0;
  toolbox_surface_rect.y=SCREEN_HEIGHT*0.84;
  toolbox_surface_rect.w=SCREEN_WIDTH*0.75;
  toolbox_surface_rect.h=SCREEN_HEIGHT*0.16;
  SDL_Texture *Toolbox_Surface=SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, toolbox_surface_rect.w,toolbox_surface_rect.h);
  //SDL_FillRect(Toolbox_Surface,NULL,0xff0000);
  SDL_Rect logRect;
  logRect.x=SCREEN_WIDTH*0.75;
  logRect.y=0;
  logRect.w=SCREEN_WIDTH*0.25;
  logRect.h=SCREEN_HEIGHT;
  SDL_Texture * logsurf=SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, logRect.w,logRect.h);

  SDL_SetRenderTarget(renderer,Main_Game_Surface);
  SDL_RenderClear(renderer);
  SDL_SetRenderDrawColor(renderer,0,0,0,255);
  SDL_SetRenderTarget(renderer,Toolbox_Surface);
  SDL_RenderClear(renderer);
  SDL_SetRenderDrawColor(renderer,0,0,0,255);
  SDL_SetRenderTarget(renderer,NULL);
  SDL_SetRenderTarget(renderer,logsurf);
  SDL_RenderClear(renderer);
  SDL_SetRenderDrawColor(renderer,0,255,0,255);
  SDL_SetRenderTarget(renderer,NULL);
  //  SDL_SetRenderTarget(renderer,Toolbox_Surface);
  //INFO SURFACE AND CONSOLE
  Game game;

  InfoSurface myLog(logRect.w,logRect.h,126,127,127,255,logfont);
  myLog.setposition(logRect.x,logRect.y);
  myLog.AddText(string("Log Test"),126,127,127);
  ScriptHandler sh(LuaHandler,&game);
  ScriptConsole console(SCREEN_WIDTH,SCREEN_HEIGHT*0.3,0,0,0,120,consolefont,&sh);
  console.setTextColor(220,220,0);
  game.Log=&myLog;

  //GAME ENGINE


  GameEngine *GE=new GameEngine();
  if(!GE->Init("Resources/init.xml",&main_surface_rect))
    {
      cout<<"Failed to Initialize"<<endl;
      return -1;
    }
  //UI
  Camera *ui_cam=new Camera(&toolbox_surface_rect,pair<int,int>(0,0));
   UI *ui=new UI(GE->getTurnEngine(),ui_cam,black_magic_font);
  
  
  game.mindex= MapIndex::Instance();
  game.map= MapIndex::Instance()->getMap();
  //initializing lua
  lua_State *lua_state;
  lua_state = luaL_newstate();
  static const luaL_Reg lualibs[] =
    {
      { "base", luaopen_base },
      { NULL, NULL}
    };

  const luaL_Reg *lib = lualibs;
  for(; lib->func != NULL; lib++)
    {
      lib->func(lua_state);
      lua_settop(lua_state, 0);
    }
  game.lua_state=lua_state;
  lua_register_everything(lua_state);
  luaL_dofile(lua_state,"Resources/init.lua");
  
  cout<<"Entering Main Game Loop"<<endl;
    int FPS=45;
    bool done=false;
  while (!done)
    {
      Uint32 start=SDL_GetTicks();
      // message processing loop
      SDL_Event event;
      while (SDL_PollEvent(&event))
        {
	  
	  // check for messages
	  int xpos,ypos;
	  SDL_GetMouseState(&xpos, &ypos);

	   if(Colision::PointInRect(pair<int,int>(xpos,ypos),main_surface_rect))
	    {
	      GE->Handle_Events(&event);
	    }
	   
	  switch (event.type)
            {
	      // exit if the window is closed
            case SDL_QUIT:
	      done = true;
	      break;
            case SDL_KEYDOWN:
	      {
                // exit if ESCAPE is pressed
                if (event.key.keysym.sym == SDLK_ESCAPE)
		  done = true;
                else if(event.key.keysym.sym==SDLK_TAB)
		  console.SetActive(!console.IsActive());
		else if(console.IsActive())
		  console.Handle_Input(event);
		else
		  {
		     ui->HandleEvents(&event);
		  }
	      }
	      break;
	      case SDL_MOUSEBUTTONDOWN:
		{
	  if(ui->Shown())
		    {
		      ui->HandleEvents(&event);
		    }
		  // si.HandleEvents(&event);
		}
		break;
	    }
	  // end switch
	} // end of message processing

      
      //cursor.Update();

      GE->Update(0.1);
      // DRAWING STARTS HERE
      
      // clear screen
      SDL_RenderClear(renderer);
      SDL_SetRenderDrawColor(renderer,0,0,0,255);
      GE->Draw(Main_Game_Surface);
      if(console.IsActive())
      console.Show(Main_Game_Surface);

      SDL_RenderCopy(renderer,Main_Game_Surface,NULL,&main_surface_rect);

      ui->Draw(NULL,Toolbox_Surface);
      SDL_RenderCopy(renderer,Toolbox_Surface,NULL,&toolbox_surface_rect);
      SDL_SetRenderTarget(renderer,NULL);
      myLog.Show(logsurf);
      SDL_RenderCopy(renderer,logsurf,NULL,&logRect);
      
      SDL_RenderPresent(renderer);
      //cout<<"FPS:"<<1000.0/(SDL_GetTicks()-start)<<endl;
      if(1000.0/FPS>SDL_GetTicks()-start)
	{
	  
	  SDL_Delay(1000.0/FPS-(SDL_GetTicks()-start));
	  
	}


    } // end main loop

  //Delete the game stuff
  delete ui_cam;
  delete GE;
  delete ui;
  
  //SDL_FreeSurface(screen);
  SDL_DestroyTexture(Main_Game_Surface);
  SDL_DestroyTexture(Toolbox_Surface);
  SDL_DestroyTexture(logsurf);
  
  TTF_CloseFont(f);
  TTF_CloseFont(fsmall);
  TTF_CloseFont(consolefont);
  TTF_CloseFont(logfont);
  TTF_CloseFont(movesfont);
  TTF_CloseFont(black_magic_font);
  Mix_FreeMusic(menu_theme);
  Mix_Quit();
  lua_close(lua_state);
  TTF_Quit();
  SDL_DestroyWindow(window);
  SDL_Quit();
  // all is well ;)
  printf("Exited cleanly\n");
  return 0;
}
