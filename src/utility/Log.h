#include "InfoSurface.h"
#ifndef __M_LOG__
#define __M_LOG__

//Singleton Infosurface wrapper to use as a log
class GlobalLog
{
 private:
    static GlobalLog *g_log;
  InfoSurface *infosurf;
  GlobalLog();
 public:
  void Init(InfoSurface *infosurf);
  void Init(int width,int height,unsigned char r,unsigned char g,unsigned char b,int a,TTF_Font *font);

  static GlobalLog* Instance();
  void Free();
};


#endif
