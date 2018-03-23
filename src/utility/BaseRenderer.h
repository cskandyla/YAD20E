#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <string>
using std::string;
class BaseRenderer
{
 private:
  SDL_Renderer *renderer;
  BaseRenderer();
 public:
  bool Init(SDL_Renderer *renderer);
  void Free();
  static BaseRenderer  *b_renderer;
  static BaseRenderer* Instance();
  SDL_Renderer* Renderer();
  SDL_Texture* LoadImage(string textureimage);
  void RenderTexture(SDL_Texture *srctexture,SDL_Texture *tgttexture,SDL_Rect *srcrect,SDL_Rect *tgtrect);
  void Render(SDL_Texture *tex,SDL_Rect *tgtrect);
  void RenderPart(SDL_Texture *tex,SDL_Rect *srcrect,SDL_Rect *tgtrect);
};
