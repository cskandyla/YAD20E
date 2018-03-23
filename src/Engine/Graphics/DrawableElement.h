#include <utility>
using std::pair;

#ifndef __DRAWABLE_ELEMENT__
#define __DRAWABLE_ELEMENT__


enum dynamic_element_typez{D_CHARACTER=0,D_ITEM,D_WALLSPELL};
class DrawableElement
{
 private:
  int zindex;
  pair<int,int> pos;
  void *obj_ptr;
  dynamic_element_typez obj_type;
 public:
  DrawableElement(int zindex,pair<int,int> pos,void *obj_ptr,dynamic_element_typez obj_type);
  int GetZIndex();
  pair<int,int> GetPos();
  void* GetObject();
  dynamic_element_typez GetObjectType();
};
bool sort_dynamic_map_elementsz(DrawableElement elem1,DrawableElement elem2);
#endif
