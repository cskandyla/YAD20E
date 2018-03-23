#include "CharacterSheet.h"
#include "BasicCharacter.h"
#include "miscellaneous.h"

CharacterSheet::CharacterSheet(TTF_Font *desc_font,BaseCharacter *the_char,int w,int h):desc_font(desc_font)
{
  attribs=the_char->getCurrentAttributes();
  stats=the_char->getGeneralStats();
  combatstats=the_char->getCombatStats();
  info=the_char->getInfo();
   visible=false;
   sheet_surf=;
  //Portrait
  //SDL_Surface *portrait=the_char->getPortrait();
  //Dummy Till I get one done
  BuildInfo();
}

CharacterSheet::CharacterSheet(TTF_Font *desc_font,BaseCharacter *the_char,string backgroundimg):desc_font(desc_font)
{

  attribs=the_char->getCurrentAttributes();
  stats=the_char->getGeneralStats();
  combatstats=the_char->getCombatStats();
  info=the_char->getInfo();
   visible=false;
  sheet_surf=loadSurface(backgroundimg.c_str());
  //Portrait
  portrait=the_char->GetPortrait();
  //Dummy Till I get one done
  BuildInfo();
}


CharacterSheet::~CharacterSheet()
{

  SDL_DestroyTexture(sheet_surf);
}




void CharacterSheet::CreateTextPair(string label_txt,string info_txt,int x,int y)
{
  SDL_Color desc_color;
  desc_color.r=0;
  desc_color.g=0;
  desc_color.b=80;

  SDL_Color info_color;
  info_color.r=0;
  info_color.g=0;
  info_color.b=255;
  SDL_Surface *label_surf=TTF_RenderText_Solid(desc_font,label_txt.c_str(),desc_color);
  SDL_Rect pos_rect;
  pos_rect.x=x;
  pos_rect.y=y;
  pos_rect.w=label_surf->w;
  pos_rect.h=label_surf->h;
  SDL_BlitSurface(label_surf,NULL,sheet_surf,&pos_rect);
  
  SDL_Surface *info_surf=TTF_RenderText_Solid(desc_font,info_txt.c_str(),info_color);
  pos_rect.x=x+pos_rect.w;
  pos_rect.w=info_surf->w;
  pos_rect.h=info_surf->h;
  SDL_BlitSurface(info_surf,NULL,sheet_surf,&pos_rect);
  SDL_FreeSurface(label_surf);
  SDL_FreeSurface(info_surf);
}

void CharacterSheet::BuildInfo()
{
  bool nul=false;
  if(portrait==NULL)
    {
      SDL_Surface *portrait=SDL_CreateRGBSurface(0,128,128,32,0x00,0x00,0x00,0x00);
      SDL_FillRect(portrait,NULL,0xFF2020);
      nul=true;
    }
  SDL_Rect portrait_rect;
  portrait_rect.x=(sheet_surf->w-portrait->w)/2;
  portrait_rect.y=0;
  portrait_rect.w=portrait->w;
  portrait_rect.h=portrait->h;
  SDL_BlitSurface(portrait,NULL,sheet_surf,&portrait_rect);
  if(nul)
  SDL_FreeSurface(portrait);
  
 //Info
  int h=portrait_rect.h+portrait_rect.y+8;
  int fontheight=TTF_FontHeight(desc_font);
  CreateTextPair("Name:",info->getName(),sheet_surf->w/4,h);
  h+=fontheight;
  CreateTextPair("Class:",info->getClass(),sheet_surf->w/4,h);
  h+=fontheight;
  CreateTextPair("Race:",info->getRace(),sheet_surf->w/4,h);
  h+=fontheight;
  CreateTextPair("Gender:",info->getGender(),sheet_surf->w/4,h);
  h+=fontheight;
  CreateTextPair(" "," ",sheet_surf->w/4,h);
  h+=fontheight;
  char text[12];
  sprintf(text,"%d",attribs->getStr());
  CreateTextPair("Strength:",text,sheet_surf->w/4,h);
  h+=fontheight;
    sprintf(text,"%d",attribs->getDex());
  CreateTextPair("Dexterity:",text,sheet_surf->w/4,h);
  h+=fontheight;
      sprintf(text,"%d",attribs->getInt());
  CreateTextPair("Intelligence:",text,sheet_surf->w/4,h);
  h+=fontheight;
      sprintf(text,"%d",attribs->getCon());
  CreateTextPair("Constitution:",text,sheet_surf->w/4,h);
  h+=fontheight;
      sprintf(text,"%d",attribs->getSpi());
  CreateTextPair("Spirit:",text,sheet_surf->w/4,h);
  h+=fontheight;
  CreateTextPair(" "," ",sheet_surf->w/4,h);
  h+=fontheight;
  sprintf(text,"%d",stats->getHp());
  CreateTextPair("Hit Points:",text,sheet_surf->w/4,h);
  h+=fontheight;
  sprintf(text,"%d",stats->getSpeed());
  CreateTextPair("Speed:",text,sheet_surf->w/4,h);
  h+=fontheight;
  sprintf(text,"%d",stats->getXp());
  CreateTextPair("Expirience:",text,sheet_surf->w/4,h);
  h+=fontheight;
  sprintf(text,"%d",stats->getLevel());
  CreateTextPair("Level:",text,sheet_surf->w/4,h);
  h+=fontheight;
  
  
  
  
}





void CharacterSheet::Draw(SDL_Surface *screen)
{
  if(visible)
    SDL_BlitSurface(sheet_surf,NULL,screen,NULL);
}
bool CharacterSheet::Shown()
  {
    return visible;
  }
void CharacterSheet::Show(bool visible)
  {
    this->visible=visible;

  }
