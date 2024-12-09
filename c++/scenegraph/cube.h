#include <memory>
class Cube;
using CubePtr = std::shared_ptr<Cube>; 

#ifndef CUBE_H
#define CUBE_H

#include "shape.h"

class Cube : public Shape {
  unsigned int m_vao;
protected:
  Cube ();
public:
  static CubePtr Make ();
  virtual ~Cube ();
  virtual void Draw (StatePtr st);
};
#endif