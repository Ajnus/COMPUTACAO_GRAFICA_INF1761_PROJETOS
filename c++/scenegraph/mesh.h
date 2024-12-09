#include <memory>
class Mesh;
using MeshPtr = std::shared_ptr<Mesh>; 

#ifndef MESH_H
#define MESH_H

#include "shape.h"
#include <string>

class Mesh : public Shape {
  unsigned int m_vao;
  unsigned int m_nind;  // number of indices
protected:
  Mesh (const std::string& filename);
  Mesh ();
public:
  static MeshPtr Make (const std::string& filename);
  static MeshPtr Make ();
  virtual ~Mesh ();
  void SetCoordBuffer (int size, const float* data, int ncomp, int stride);
  void SetNormalBuffer (int size, const float* data, int ncomp, int stride);
  void SetTangentBuffer (int size, const float* data, int ncomp, int stride);
  void SetTexCoordBuffer (int size, const float* data, int ncomp, int stride);
  void SetIndexBuffer (int size, const unsigned int* data);
  virtual void Draw (StatePtr st);
};
#endif