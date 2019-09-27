#include "Label.h"
#include "BaseRenderer.h"
SimpleLabel::SimpleLabel(string label_text,TTF_Font *font)
{
	SDL_Surface *new_surf=TTF_RenderText_Solid(font,label_text.c_str(),SDL_Color {255,255,255});
        this->background=SDL_CreateTextureFromSurface(BaseRenderer::Instance()->Renderer(), new_surf);
	SDL_FreeSurface(new_surf);
}

SimpleLabel::~SimpleLabel()
{
	SDL_DestroyTexture(background);
}
void SimpleLabel::Draw(int x,int y,SDL_Texture *screen)
{
	this->font=font;
	SDL_Rect pos;
	pos.x=x;
	pos.y=y;
	SDL_QueryTexture( background, NULL, NULL, &pos.w, &pos.h );
	BaseRenderer::Instance()->RenderTexture(background,screen,NULL,&pos);
}


void SimpleLabel::Update(string new_text)
{
	if(background)
	  SDL_DestroyTexture(background);
		SDL_Surface *new_surf=TTF_RenderText_Solid(font,label_text.c_str(),SDL_Color {255,255,255});
        this->background=SDL_CreateTextureFromSurface(BaseRenderer::Instance()->Renderer(), new_surf);
	 SDL_FreeSurface(new_surf);
}
