#include "triangle.h"

#include <iostream>

#include "glad.h"
#include <GLFW/glfw3.h>

TrianglePtr Triangle::Make ()
{
  return TrianglePtr(new Triangle());
}

Triangle::Triangle ()
{
  float coord[] = {-1.0f,0.0f,1.0f,0.0f,0.0f,1.0f};
  // create VAO
  glGenVertexArrays(1,&m_vao);
  glBindVertexArray(m_vao);
  // create coord buffer
  GLuint id;
  glGenBuffers(1,&id);
  glBindBuffer(GL_ARRAY_BUFFER,id);
  glBufferData(GL_ARRAY_BUFFER,sizeof(coord),coord,GL_STATIC_DRAW);
  glVertexAttribPointer(0,2,GL_FLOAT,GL_FALSE,0,0);  // coord
  glEnableVertexAttribArray(0);
}

Triangle::~Triangle () 
{
}

void Triangle::Draw (StatePtr )
{
  glBindVertexArray(m_vao);
  glDrawArrays(GL_TRIANGLES,0,3);
}