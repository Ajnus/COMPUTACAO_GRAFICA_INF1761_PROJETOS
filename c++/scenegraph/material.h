#include <memory>
class Material;
using MaterialPtr = std::shared_ptr<Material>; 

#ifndef MATERIAL_H
#define MATERIAL_H

#include "appearance.h"
#include <glm/glm.hpp>

class Material : public Appearance {
  glm::vec4 m_amb; 
  glm::vec4 m_dif; 
  glm::vec4 m_spe;
  float m_shi;
  float m_opacity;
protected:
  Material (float r, float g, float b, float opacity);
public:
  static MaterialPtr Make (float r, float g, float b, float opacity=1.0f);
  virtual ~Material ();
  void SetAmbient (float r, float g, float b);
  void SetDiffuse (float r, float g, float b);
  void SetSpecular (float r, float g, float b);
  void SetShininess (float shi);
  void SetOpacity (float opacity);
  virtual void Load (StatePtr st);
};

#endif