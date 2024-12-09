#include "state.h"
#include "shader.h"
#include "camera.h"
#include "shader.h"

#include <glm/gtc/matrix_transform.hpp>

#include "glad.h"
#include <GLFW/glfw3.h>

#include <iostream>
#include <cstdlib>

StatePtr State::Make(CameraPtr camera)
{
  return StatePtr(new State(camera));
}

State::State(CameraPtr camera)
    : m_camera(camera),
      m_shader(),
      m_stack{glm::mat4(1.0f)}
{
  glUseProgram(0); // compatibility profile as default
}

State::~State()
{
}

void State::PushShader(ShaderPtr shd)
{
  m_shader.push_back(shd);
  shd->UseProgram();
}

void State::PopShader()
{
  m_shader.pop_back();
  if (m_shader.empty())
    glUseProgram(0);
  else
    m_shader.back()->UseProgram();
}

ShaderPtr State::GetShader() const
{
  if (m_shader.empty())
  {
    std::cerr << "Shader not defined";
    exit(1);
  }
  return m_shader.back();
}

CameraPtr State::GetCamera() const
{
  return m_camera;
}

void State::PushMatrix()
{
  m_stack.push_back(GetCurrentMatrix());
}

void State::PopMatrix()
{
  m_stack.pop_back();
}

void State::LoadMatrix(const glm::mat4 &mat)
{
  m_stack.back() = mat;
}

void State::MultMatrix(const glm::mat4 &mat)
{
  m_stack.back() = m_stack.back() * mat;
}

const glm::mat4 &State::GetCurrentMatrix() const
{
  return m_stack.back();
}

void State::SetMatrices()
{
  // set matrices
  ShaderPtr shd = GetShader();
  glm::mat4 mvp = m_camera->GetProjMatrix() *
                  m_camera->GetViewMatrix() *
                  GetCurrentMatrix();
  shd->SetUniform("Mvp", mvp);
}