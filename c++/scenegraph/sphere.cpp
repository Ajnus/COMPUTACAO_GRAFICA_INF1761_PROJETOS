#include "sphere.h"
#include "grid.h"
#include "error.h"

#include <cmath>
#include <iostream>

#include "glad/glad.h"
#include <GLFW/glfw3.h>

#define PI 3.14159265f

SpherePtr Sphere::Make(int nstack, int nslice)
{
  return SpherePtr(new Sphere(nstack, nslice));
}

Sphere::Sphere(int nstack, int nslice)
{
  GridPtr grid = Grid::Make(nstack, nslice);
  m_nind = grid->IndexCount();

  // generate spherical coordinates
  float *coord = new float[3 * (nstack + 1) * (nslice + 1)];
  float *tangent = new float[3 * (nstack + 1) * (nslice + 1)];

  int nc = 0;

  const float *texcoord = grid->GetCoords();

  for (int i = 0; i < 2 * grid->VertexCount(); i += 2)
  {
    float theta = texcoord[i + 0] * 2 * PI;
    float phi = texcoord[i + 1] * PI;
    coord[nc + 0] = sin(theta) * sin(PI - phi);
    coord[nc + 1] = cos(PI - phi);
    coord[nc + 2] = cos(theta) * sin(PI - phi);
    tangent[nc + 0] = cos(theta);
    tangent[nc + 1] = 0;
    tangent[nc + 2] = -sin(theta);
    nc += 3;
  }
  // create VAO
  glGenVertexArrays(1, &m_vao);
  glBindVertexArray(m_vao);

  // create buffers
  GLuint id[3]; // buffers: coord/normal, tangent, texcoord
  glGenBuffers(3, id);

  glBindBuffer(GL_ARRAY_BUFFER, id[0]);
  glBufferData(GL_ARRAY_BUFFER, 3 * grid->VertexCount() * sizeof(float), coord, GL_STATIC_DRAW);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
  glEnableVertexAttribArray(0);
  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
  glEnableVertexAttribArray(1);

  glBindBuffer(GL_ARRAY_BUFFER, id[1]);
  glBufferData(GL_ARRAY_BUFFER, 3 * grid->VertexCount() * sizeof(float), tangent, GL_STATIC_DRAW);
  glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, 0);
  glEnableVertexAttribArray(2);

  glBindBuffer(GL_ARRAY_BUFFER, id[2]);
  glBufferData(GL_ARRAY_BUFFER, 2 * grid->VertexCount() * sizeof(float), texcoord, GL_STATIC_DRAW);
  glVertexAttribPointer(3, 2, GL_FLOAT, GL_FALSE, 0, 0);
  glEnableVertexAttribArray(3);

  // create index buffer
  GLuint index;
  glGenBuffers(1, &index);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, index);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_nind * sizeof(unsigned int), grid->GetIndices(), GL_STATIC_DRAW);
  
  delete[] tangent;
  delete[] coord;
}

Sphere::~Sphere()
{
}

void Sphere::Draw(StatePtr st)
{
  glBindVertexArray(m_vao);
  glDrawElements(GL_TRIANGLES, m_nind, GL_UNSIGNED_INT, 0);
}