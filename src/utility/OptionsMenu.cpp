#include "OptionsMenu.h"
#include "BaseRenderer.h"

/*
OptionsMenu::OptionsMenu(TTF_Font *f,int maxw,SDL_Color txtc,SDL_Texture *button,SDL_Texture *button_pressed):font(f),max_width(maxw),textcolor(txtc),button(button),button_pressed(button_pressed)
{
    position.x=0;
    position.y=0;
    Active=false;
}

void OptionsMenu::Draw(SDL_Texture *screen)
{
    for(int i=0; i<options.size(); i++)
      {
        SDL_Rect newpos;
        newpos.x=position.x+options[i].first.x;
        newpos.y=position.y+options[i].first.y;
        //SDL_BlitSurface(options[i].second,NULL,screen,&newpos);
	BaseRenderer::Instance()->RenderTexture(surfaces[i],screen,NULL,&temp);
    }
}

void OptionsMenu::AddOption(string option)
{
    int w,h;
    TTF_SizeText(font,option.c_str(),&w,&h);
    int tex_w,tex_h;
    SDL_QueryTexture(button,NULL,NULL,&tex_w,&tex_h);
    SDL_Surface *surf=SDL_CreateRGBSurface(0,tex_w,tex_h,32,0x00,0x00,0x00,0x00);
    //SDL_BlitSurface(button,NULL,surf,NULL);
    SDL_Surface* textsurf=TTF_RenderText_Solid(font,option.c_str(),textcolor);
    SDL_Rect tr;
    tr.x=(surf->w-textsurf->w)/2;
    tr.y=(surf->h-textsurf->h)/2;
    tr.w=textsurf->w;
    tr.h=textsurf->h;
      
    
    SDL_BlitSurface(textsurf,NULL,surf,&tr);
    SDL_FreeSurface(textsurf);
    optionstext.push_back(option);
    SDL_Rect r;
    r.x=0;
    r.y=optionstext.size()*tex_h;
    r.w=tex_w;
    r.h=tex_h;
    
    options.push_back(pair<SDL_Rect,SDL_Surface*>(r,SDL_CreateTextureFromSurface(  BaseRenderer::Instance()->Renderer(), surf)));
}

void OptionsMenu::SetPosition(int x,int y)
{
    position.x=x;
    position.y=y;


}



string OptionsMenu::getOptionPressed(int x,int y)
{
    x=x-position.x;
    y=y-position.y;
    for(int i=0; i<options.size(); i++)
    {
        if(x <= options[i].first.w+options[i].first.x && x >= options[i].first.x && y <= options[i].first.h+options[i].first.y && y >= options[i].first.y)
            return optionstext[i];
    }

    return "NONE";



}


void OptionsMenu::MakeHighlighted(int x,int y)
{

  
    x=x-position.x;
    y=y-position.y;
    int tex_w,tex_h;
    SDL_QueryTexture(button,NULL,NULL,&tex_w,&tex_h);
    for(int i=0; i<options.size(); i++)
    {
        if(x <= options[i].first.w+options[i].first.x && x >= options[i].first.x && y <= options[i].first.h+options[i].first.y && y >= options[i].first.y)
        {
            SDL_FreeSurface(options[i].second);
            SDL_Surface *surf=SDL_CreateRGBSurface(0,tex_w,tex_h,32,0x00,0x00,0x00,0x00);
	    
	    SDL_BlitSurface(button_pressed,NULL,surf,NULL);
	    SDL_Surface *textsurf=TTF_RenderText_Solid(font,optionstext[i].c_str(),textcolor);
	    SDL_Rect tr;
	    tr.x=(surf->w-textsurf->w)/2;
	    tr.y=(surf->h-textsurf->h)/2;
	    tr.w=textsurf->w;
	    tr.h=textsurf->h;
	    

            SDL_BlitSurface(textsurf,NULL,surf,&tr);
	    
            options[i].second=SDL_CreateTextureFromSurface(  BaseRenderer::Instance()->Renderer(), surf);

        }
        else
        {
            SDL_FreeSurface(options[i].second);
	    SDL_Surface *surf=SDL_CreateRGBSurface(0,tex_w,tex_h,32,0x00,0x00,0x00,0x00);
            SDL_BlitSurface(button,NULL,surf,NULL);
            SDL_Surface *textsurf=TTF_RenderText_Solid(font,optionstext[i].c_str(),textcolor);
	    SDL_Rect tr;
	    tr.x=(surf->w-textsurf->w)/2;
	    tr.y=(surf->h-textsurf->h)/2;
	    tr.w=textsurf->w;
	    tr.h=textsurf->h;
            //SDL_BlitSurface(textsurf,NULL,surf,&tr);
            SDL_SetRenderTarget(BaseRenderer::Instance()->Renderer(),background);
	    SDL_SetRenderDrawColor(BaseRenderer::Instance()->Renderer(),0,0,0,255);
	    SDL_RenderClear(BaseRenderer::Instance()->Renderer());
            
	    
            options[i].second=SDL_CreateTextureFromSurface(  BaseRenderer::Instance()->Renderer(), surf);

        }
    }
  



}

bool OptionsMenu::IsActive()
{

    return Active;
}

void OptionsMenu::SetActive(bool Active)
{

    this->Active=Active;

}
*/
