#include <memory>
class SkyBox;
using SkyBoxPtr = std::shared_ptr<SkyBox>; 

#ifndef SKY_BOX_H
#define SKY_BOX_H

#include "shape.h"

class SkyBox : public Shape {
  unsigned int m_vao;
  unsigned int m_coord_buffer;
protected:
  SkyBox ();
public:
  static SkyBoxPtr Make ();
  virtual ~SkyBox ();
  virtual void Draw (StatePtr st);
};
#endif