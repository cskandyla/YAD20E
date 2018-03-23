
//Singleton Infosurface wrapper to use as a log
class GlobalLog
{
 private:
  InfoSurface *infosurf;
 public:
  void Init(InfoSurface *infosurf);
  void Init(int width,int height,unsigned char r,unsigned char g,unsigned char b,int a,TTF_Font *font);

  static GlobalLog* Instance();
  void Free();
};
