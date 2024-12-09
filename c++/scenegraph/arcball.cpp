#include "arcball.h"


#include "glad/glad.h"
#include <GLFW/glfw3.h>
#include <cmath>
#include <iostream>

#include <glm/glm.hpp>
#include <glm/mat4x4.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/string_cast.hpp>

#define PI 3.14159265f

// Map function: from screen (x,y) to unit sphere (px,py,pz)
static void Map (int width, int height, int x, int y, float* px, float* py, float* pz)
{
  float r = width < height ? width/2.0f : height/2.0f;
  float X = (x - width/2.0f) / r;
  float Y = (y - height/2.0f) / r;
  float Z;
  float l = sqrt(X*X + Y*Y);
  if (l <= 1.0f) {
    Z = sqrt(1.0f - l*l);
  }
  else {
    X /= l;
    Y /= l;
    Z = 0.0f;
  }
  *px = X;
  *py = Y;
  *pz = Z;
}

ArcballPtr Arcball::Make (float distance)
{
  return ArcballPtr(new Arcball(distance));
}

Arcball::Arcball (float distance) 
: m_distance(distance), m_x0(0), m_y0(0), m_mat(1.0f)
{
}

void Arcball::InitMouseMotion (int x0, int y0)
{
  m_x0 = x0;
  m_y0 = y0;
}

void Arcball::AccumulateMouseMotion (int x, int y)
{
  int vp[4];  // vp dimension: {x0, y0, w, h} 
  glGetIntegerv(GL_VIEWPORT,vp);  
  if (x==m_x0 && y==m_y0)
    return;
  float ux, uy, uz;
  float vx, vy, vz;
  Map(vp[2],vp[3],m_x0,m_y0,&ux,&uy,&uz);
  Map(vp[2],vp[3],x,y,&vx,&vy,&vz);
  m_x0 = x;
  m_y0 = y;
  float ax = uy*vz - uz*vy;
  float ay = uz*vx - ux*vz;
  float az = ux*vy - uy*vx;
  float theta = 2*asin(sqrt(ax*ax+ay*ay+az*az)); 
  // m_mat = T * R * T
  glm::mat4 m(1.0f);
  m = glm::translate(m,glm::vec3(0.0f,0.0f,-m_distance));
  m = glm::rotate(m,theta,glm::vec3(ax,ay,az));
  m = glm::translate(m,glm::vec3(0.0f,0.0f,m_distance));
  m_mat = m * m_mat;
}

const glm::mat4& Arcball::GetMatrix () const
{
  return m_mat;
}
