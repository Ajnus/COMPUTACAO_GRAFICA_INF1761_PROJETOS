#include <memory>
class ClipPlane;
using ClipPlanePtr = std::shared_ptr<ClipPlane>; 

#ifndef CLIP_PLANE_H
#define CLIP_PLANE_H

#include "appearance.h"
#include <glm/glm.hpp>
#include <vector>

class ClipPlane : public Appearance {
  std::string m_name;
  std::string m_colorname;
  glm::vec4 m_color;
  std::vector<glm::vec4> m_planes; 
protected:
  ClipPlane (const std::string& name);
  ClipPlane (const std::string& name, float a, float b, float c, float d);
public:
  static ClipPlanePtr Make (const std::string& name);
  static ClipPlanePtr Make (const std::string& name, float a, float b, float c, float d);
  virtual ~ClipPlane ();
  void AddPlane (float a, float b, float c, float d);
  void SetColor (const std::string& varname, float r, float g, float b);
  virtual void Load (StatePtr st);
  virtual void Unload (StatePtr st);
};

#endif