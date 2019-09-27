// screen resolution
#define SCREEN_WIDTH 1920
#define SCREEN_HEIGHT 1080
//#define SCREEN_WIDTH 1280
//#define SCREEN_HEIGHT 960
//map parameters
#define TILE_SIZE 30
#define SCROLL_SPEED 10
//inventory parameters
#define NUM_OF_SLOTS 24
#define SLOT_SIZE 30

/*
#define    rmask  0
#define    gmask  0
#define    bmask  0
#define    amask  0
*/

#if SDL_BYTEORDER == SDL_BIG_ENDIAN
#define    rmask  0xff000000
#define    gmask  0x00ff0000
#define    bmask  0x0000ff00
#define    amask  0x000000ff
#else
#define    rmask  0x000000ff
#define    gmask  0x0000ff00
#define    bmask  0x00ff0000
#define    amask  0xff000000
#endif

