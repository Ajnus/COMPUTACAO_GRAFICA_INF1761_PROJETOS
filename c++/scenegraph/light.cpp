#include "light.h"
#include "node.h"
#include "state.h"
#include "shader.h"
#include "camera.h"


#include "glad/glad.h"
#include <GLFW/glfw3.h>

LightPtr Light::Make (float x, float y, float z, float w, const std::string& space)
{
  return LightPtr(new Light(x,y,z,w,space));
}

Light::Light (float x, float y, float z, float w, const std::string& space)
: m_space(space),
  m_amb{0.3f,0.3f,0.3f,1.0f},
  m_dif{0.7f,0.7f,0.7f,1.0f},
  m_spe{1.0f,1.0f,1.0f,1.0f},
  m_pos{x,y,z,w},
  m_reference(nullptr)
{
}

Light::~Light ()
{
}

void Light::SetAmbient (float r, float g, float b)
{
  m_amb[0] = r;
  m_amb[1] = g;
  m_amb[2] = b;
}

void Light::SetDiffuse (float r, float g, float b)
{
  m_dif[0] = r;
  m_dif[1] = g;
  m_dif[2] = b;
}

void Light::SetSpecular (float r, float g, float b)
{
  m_spe[0] = r;
  m_spe[1] = g;
  m_spe[2] = b;
}

void Light::SetReference (NodePtr reference)
{
  m_reference = reference;
}

NodePtr Light::GetReference () const
{
  return m_reference;
}

void Light::SetPosition (float x, float y, float z, float w)
{
  m_pos[0] = x;
  m_pos[1] = y;
  m_pos[2] = z;
  m_pos[3] = w;
}

void Light::Load (StatePtr st) const
{
  ShaderPtr shd = st->GetShader();
  shd->SetUniform("lamb",m_amb);
  shd->SetUniform("ldif",m_dif);
  shd->SetUniform("lspe",m_spe);

  // Set position in the lighting space
  glm::mat4 M(1.0f);
  if (m_space == "world" && shd->GetLightingSpace() == "camera") {
    M = st->GetCamera()->GetViewMatrix();
  }
  else if (m_space == "camera" && shd->GetLightingSpace() == "world") {
    M = glm::inverse(st->GetCamera()->GetViewMatrix());
  }
  if (GetReference()) {
    M = M * GetReference()->GetModelMatrix();
  }
  glm::vec4 pos = M * m_pos;
  shd -> SetUniform ("lpos",pos);
}