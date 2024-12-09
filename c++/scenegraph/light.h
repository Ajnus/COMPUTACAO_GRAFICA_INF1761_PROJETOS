#include <memory>
class Light;
using LightPtr = std::shared_ptr<Light>; 

#ifndef LIGHT_H
#define LIGHT_H

#include "node.h"
#include <glm/glm.hpp>
#include <string>

class Light {
  std::string m_space;
  glm::vec4 m_amb;
  glm::vec4 m_dif;
  glm::vec4 m_spe;
  glm::vec4 m_pos;
  NodePtr m_reference;
protected:
  Light (float x, float y, float z, float w, const std::string& space);
public:
  static LightPtr Make (float x, float y, float z, float w=1.0f, const std::string& space="world");
  virtual ~Light ();
  void SetPosition (float x, float y, float z,float w=1.0f);
  void SetAmbient (float r, float g, float b);
  void SetDiffuse (float r, float g, float b);
  void SetSpecular (float r, float g, float b);
  void SetReference (NodePtr reference);
  NodePtr GetReference () const;
  void Load (StatePtr st) const;
};

#endif