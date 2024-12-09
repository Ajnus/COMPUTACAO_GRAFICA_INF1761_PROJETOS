#include <memory>
class Transform;
using TransformPtr = std::shared_ptr<Transform>; 

#ifndef TRANSFORM_H
#define TRANSFORM_H

#include <glm/glm.hpp>

#include "state.h"

class Transform {
  glm::mat4 m_mat;
protected:
  Transform ();
public:
  static TransformPtr Make ();
  virtual ~Transform ();
  void LoadIdentity ();
  void MultMatrix (const glm::mat4 mat);
  void Translate (float x, float y, float z);
  void Scale (float x, float y, float z);
  void Rotate (float angle, float x, float y, float z);
  const glm::mat4& GetMatrix () const;
  void Load (StatePtr st) const;
  void Unload (StatePtr st) const;
};

#endif