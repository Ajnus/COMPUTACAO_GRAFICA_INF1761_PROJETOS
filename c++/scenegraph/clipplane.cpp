#include "clipplane.h"
#include "shader.h"
#include "state.h"

#include "glad/glad.h"
#include <GLFW/glfw3.h>

ClipPlanePtr ClipPlane::Make(const std::string &name)
{
  return ClipPlanePtr(new ClipPlane(name));
}
ClipPlanePtr ClipPlane::Make(const std::string &name, float a, float b, float c, float d)
{
  return ClipPlanePtr(new ClipPlane(name, a, b, c, d));
}
ClipPlane::ClipPlane(const std::string &name)
    : m_name(name)
{
}
ClipPlane::ClipPlane(const std::string &name, float a, float b, float c, float d)
    : m_name(name),
      m_colorname("planecolor"),
      m_color(glm::vec4(1.0f, 1.0f, 1.0f, 1.0f))
{
  AddPlane(a, b, c, d);
}
ClipPlane::~ClipPlane()
{
}
void ClipPlane::AddPlane(float a, float b, float c, float d)
{
  m_planes.push_back(glm::vec4(a, b, c, d));
}

void ClipPlane::SetColor(const std::string &varname, float r, float g, float b)
{
  m_colorname = varname;
  m_color.r = r;
  m_color.g = g;
  m_color.b = b;
  m_color.a = 1.0f;
}
void ClipPlane::Load(StatePtr st)
{
  ShaderPtr shd = st->GetShader();
  glm::mat4 mat = st->GetCurrentMatrix(); // model
  if (shd->GetLightingSpace() == "camera")
    mat = st->GetCamera()->GetViewMatrix() * mat;
  glm::mat4 mit = glm::transpose(glm::inverse(mat));
  std::vector<glm::vec4> planes;
  int i = 0;
  for (auto p : m_planes)
  {
    planes.push_back(mit * p);
    glEnable(GL_CLIP_DISTANCE0 + i++);
  }
  shd->SetUniform(m_name, planes);
  shd->SetUniform(m_colorname, m_color);

  for (int i = 0; i < m_planes.size(); ++i)
    glEnable(GL_CLIP_DISTANCE0 + i);
}
void ClipPlane::Unload(StatePtr)
{
  for (int i = 0; i < m_planes.size(); ++i)
    glDisable(GL_CLIP_DISTANCE0 + i);
}
