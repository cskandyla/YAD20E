#include "DrawableElement.h"


DrawableElement::DrawableElement(int zindex,pair<int,int> pos,void *obj_ptr,dynamic_element_typez obj_type):zindex(zindex),pos(pos),obj_ptr(obj_ptr),obj_type(obj_type)
{
  
}

int DrawableElement::GetZIndex()
{
  return this->zindex;
}

pair<int,int> DrawableElement::GetPos()
{
  return this->pos;
}

void* DrawableElement::GetObject()
{
  return this->obj_ptr;
}

dynamic_element_typez DrawableElement::GetObjectType()
{
  return this->obj_type;
}


bool sort_dynamic_map_elementsz(DrawableElement elem1,DrawableElement elem2)
{
  if(elem1.GetZIndex()==elem2.GetZIndex())
    return (elem1.GetPos().second<elem2.GetPos().second);
  else
    return (elem1.GetZIndex()<elem2.GetZIndex());
}
