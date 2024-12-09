#include <memory>
class Arcball;
using ArcballPtr = std::shared_ptr<Arcball>; 

#ifndef ARCBALL_H
#define ARCBALL_H

#include <glm/mat4x4.hpp>

class Arcball {
  float m_distance;
  float m_x0, m_y0;
  glm::mat4 m_mat;
protected:
  Arcball (float distance);
public:
  static ArcballPtr Make (float distance);
  void InitMouseMotion (int x, int y);
  void AccumulateMouseMotion (int x, int y);
  const glm::mat4& GetMatrix () const;
};

#endif

