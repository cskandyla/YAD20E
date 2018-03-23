#ifndef __CELLINFO__
#define __CELLINFO__

enum ENTITY_TYPE {NOTHING,CHARACTER_T,OBJECT_T,DOODAD_T};
enum COVER_TYPE  {COVER_NONE,COVER_HALF,COVER_FULL};
class CellInfo
{
private:
    ENTITY_TYPE type;
    //COVER_TYPE 
    int id;
public:
    CellInfo(int id,ENTITY_TYPE t);
    int getID();
    ENTITY_TYPE getType();


};
#endif // __CELLINFO
