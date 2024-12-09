#include <memory>
class Triangle;
using TrianglePtr = std::shared_ptr<Triangle>; 

#ifndef TRIANGLE_H
#define TRIANGLE_H

#include "shape.h"

class Triangle : public Shape {
  unsigned int m_vao;
protected:
  Triangle ();
public:
  static TrianglePtr Make ();
  virtual ~Triangle ();
  virtual void Draw (StatePtr st);
};
#endif