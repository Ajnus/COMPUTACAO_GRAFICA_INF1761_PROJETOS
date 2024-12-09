#include <memory>
class Shape;
using ShapePtr = std::shared_ptr<Shape>; 

#ifndef SHAPE_H
#define SHAPE_H

#include "state.h"

class Shape {
protected:
  Shape () {}
public:
  enum LOC {
    COORD=0,
    NORMAL,
    TANGENT,
    TEXCOORD
  };
  virtual ~Shape () {}
  virtual void Draw (StatePtr st) = 0;
};

#endif