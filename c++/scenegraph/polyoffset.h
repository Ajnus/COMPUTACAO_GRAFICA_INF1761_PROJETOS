#include <memory>
class PolygonOffset;
using PolygonOffsetPtr = std::shared_ptr<PolygonOffset>; 

#ifndef POLYOFFSET_H
#define POLYOFFSET_H

#include "appearance.h"
#include <glm/glm.hpp>
#include <vector>

class PolygonOffset : public Appearance {
  float m_factor;
  float m_units;
  PolygonOffset (float factor, float units);
public:
  static PolygonOffsetPtr Make (float factor=-1.0f, float units=-1.0f);
  virtual ~PolygonOffset ();
  virtual void Load (StatePtr st);
  virtual void Unload (StatePtr st);
};

#endif