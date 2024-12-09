#include "camera3d.h"
#include "node.h"
#include "arcball.h"
#include "state.h"
#include "transform.h"

#include <cmath>
#include <iostream>


#include "glad/glad.h"
#include <GLFW/glfw3.h>

#include <glm/gtc/matrix_transform.hpp>

Camera3DPtr Camera3D::Make (float x, float y, float z)
{
  return Camera3DPtr(new Camera3D(x,y,z));
}

Camera3D::Camera3D (float x, float y, float z)
: m_ortho(false),
  m_fovy(45.0f), m_znear(0.1f), m_zfar(1000.0f),
  m_center(0.0f,0.0f,0.0f),
  m_eye(x,y,z),
  m_up(0.0f,1.0f,0.0f),
  m_arcball(nullptr),
  m_reference(nullptr)
{
}

Camera3D::~Camera3D ()
{
}

void Camera3D::SetAngle (float fovy)
{
  m_fovy = fovy;
}

void Camera3D::SetZPlanes (float znear, float zfar)
{
  m_znear = znear;
  m_zfar = zfar;
}

void Camera3D::SetCenter (float x, float y, float z)
{
  m_center[0] = x;
  m_center[1] = y;
  m_center[2] = z;
}

void Camera3D::SetEye (float x, float y, float z)
{
  m_eye[0] = x;
  m_eye[1] = y;
  m_eye[2] = z;
}

void Camera3D::SetUpDir (float x, float y, float z)
{
  m_up[0] = x;
  m_up[1] = y;
  m_up[2] = z;
}

void Camera3D::SetOrtho (bool ortho)
{
  m_ortho = ortho;
}

ArcballPtr Camera3D::CreateArcball ()
{
  float distance = glm::distance(m_eye,m_center);
  m_arcball = Arcball::Make(distance);
  return m_arcball;
}

ArcballPtr Camera3D::GetArcball () const
{
  return m_arcball;
}

void Camera3D::SetReference (NodePtr reference)
{
  m_reference = reference;
}

glm::mat4 Camera3D::GetProjMatrix () const
{
  int viewport[4];  // viewport dimension: {x0, y0, w, h} 
  glGetIntegerv(GL_VIEWPORT,viewport);  
  if (!m_ortho) {
    float ratio = (float) viewport[2] / viewport[3];
    return glm::perspective(glm::radians(m_fovy),ratio,m_znear,m_zfar);
  }
  else {
    float distance = glm::distance(m_eye,m_center);
    float height = distance * tan(glm::radians(m_fovy)/2.0f);
    float width = height / viewport[3] * viewport[2];
    return glm::ortho(-width,width,-height,height,m_znear,m_zfar);
  }
}

glm::mat4 Camera3D::GetViewMatrix () const
{
  glm::mat4 view(1.0f);
  if (m_arcball) 
    view = view * m_arcball->GetMatrix();
  view = view * glm::lookAt(m_eye,m_center,m_up);
  if (m_reference)
      view = view * glm::inverse(m_reference->GetModelMatrix());
  return view;
}

void Camera3D::Load (StatePtr st) const
{
  ShaderPtr shd = st->GetShader();
  glm::vec4 cpos(0.0f,0.0f,0.0f,1.0f);  // in camera space
  if (shd->GetLightingSpace() == "world") {
    glm::mat4 mat = glm::inverse(GetViewMatrix());
    cpos = mat * cpos;
  }
  shd->SetUniform("cpos",cpos);
}
