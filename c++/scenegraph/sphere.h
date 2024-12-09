#include <memory>
class Sphere;
using SpherePtr = std::shared_ptr<Sphere>; 

#ifndef SPHERE_H
#define SPHERE_H

#include "shape.h"

class Sphere : public Shape {
  unsigned int m_vao;
  unsigned int m_nind; // number of incident vertices
protected:
  Sphere (int nstack, int nslice);
public:
  static SpherePtr Make (int nstack=64, int nslice=64);
  virtual ~Sphere ();
  virtual void Draw (StatePtr st);
};
#endif
