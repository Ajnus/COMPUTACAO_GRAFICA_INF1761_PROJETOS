#include "quad.h"
#include "error.h"
#include "grid.h"

#include <iostream>


#include "glad/glad.h"
#include <GLFW/glfw3.h>

QuadPtr Quad::Make (int nx, int ny)
{
  return QuadPtr(new Quad(nx,ny));
}

Quad::Quad (int nx, int ny)
{
  GridPtr grid = Grid::Make(nx,ny);
  m_nind = grid->IndexCount();
  // create VAO
  glGenVertexArrays(1,&m_vao);
  glBindVertexArray(m_vao);
  // create coord buffer
  GLuint id;
  glGenBuffers(1,&id);
  glBindBuffer(GL_ARRAY_BUFFER,id);
  glBufferData(GL_ARRAY_BUFFER,2*grid->VertexCount()*sizeof(float),grid->GetCoords(),GL_STATIC_DRAW);
  glVertexAttribPointer(0,2,GL_FLOAT,GL_FALSE,0,0);  // coord
  glEnableVertexAttribArray(0);
  glVertexAttribPointer(3,2,GL_FLOAT,GL_FALSE,0,0);  // texcoord
  glEnableVertexAttribArray(3);
  // create index buffer
  GLuint index;
  glGenBuffers(1,&index);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,index);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER,m_nind*sizeof(unsigned int),grid->GetIndices(),GL_STATIC_DRAW);
}

Quad::~Quad () 
{
}

void Quad::Draw (StatePtr )
{
  glBindVertexArray(m_vao);
  glVertexAttrib3f(1,0.0f,0.0f,1.0f); // constant for all vertices
  glVertexAttrib3f(2,1.0f,0.0f,0.0f); // constant for all vertices
  glDrawElements(GL_TRIANGLES,m_nind,GL_UNSIGNED_INT,0);
}