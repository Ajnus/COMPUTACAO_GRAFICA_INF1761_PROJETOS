#include "cube.h"
#include "error.h"


#include "glad/glad.h"
#include <GLFW/glfw3.h>

CubePtr Cube::Make ()
{
  return CubePtr(new Cube());
}

Cube::Cube ()
{
  float coords[] = { 
    // back face: counter clockwise 
    -0.5f, 0.0f,-0.5f,
    -0.5f, 1.0f,-0.5f,
     0.5f, 1.0f,-0.5f,
     0.5f, 0.0f,-0.5f,
    // front face: counter clockwise 
    -0.5f, 0.0f, 0.5f,
     0.5f, 0.0f, 0.5f,
     0.5f, 1.0f, 0.5f,
    -0.5f, 1.0f, 0.5f,
    // left face: counter clockwise
    -0.5f, 0.0f,-0.5f,
    -0.5f, 0.0f, 0.5f,
    -0.5f, 1.0f, 0.5f,
    -0.5f, 1.0f,-0.5f,
    // right face: counter clockwise
     0.5f, 0.0f,-0.5f,
     0.5f, 1.0f,-0.5f,
     0.5f, 1.0f, 0.5f,
     0.5f, 0.0f, 0.5f,
    // botton face: counter clockwise 
    -0.5f, 0.0f,-0.5f,
     0.5f, 0.0f,-0.5f,
     0.5f, 0.0f, 0.5f,
    -0.5f, 0.0f, 0.5f,
    // top face: counter clockwise
    -0.5f, 1.0f,-0.5f,
    -0.5f, 1.0f, 0.5f,
     0.5f, 1.0f, 0.5f,
     0.5f, 1.0f,-0.5f
  };
  float normals[] = {
    // back face: counter clockwise 
     0.0f, 0.0f,-1.0f,
     0.0f, 0.0f,-1.0f,
     0.0f, 0.0f,-1.0f,
     0.0f, 0.0f,-1.0f,
    // front face: counter clockwise 
     0.0f, 0.0f, 1.0f,
     0.0f, 0.0f, 1.0f,
     0.0f, 0.0f, 1.0f,
     0.0f, 0.0f, 1.0f,
    // left face: counter clockwise
    -1.0f, 0.0f, 0.0f,
    -1.0f, 0.0f, 0.0f,
    -1.0f, 0.0f, 0.0f,
    -1.0f, 0.0f, 0.0f,
    // right face: counter clockwise
     1.0f, 0.0f, 0.0f,
     1.0f, 0.0f, 0.0f,
     1.0f, 0.0f, 0.0f,
     1.0f, 0.0f, 0.0f,
    // botton face: counter clockwise 
     0.0f,-1.0f, 0.0f,
     0.0f,-1.0f, 0.0f,
     0.0f,-1.0f, 0.0f,
     0.0f,-1.0f, 0.0f,
    // top face: counter clockwise
     0.0f, 1.0f, 0.0f,
     0.0f, 1.0f, 0.0f,
     0.0f, 1.0f, 0.0f,
     0.0f, 1.0f, 0.0f,
  };
  float texcoords[] = {
    // back face: counter clockwise 
     0.0f, 0.0f,
     1.0f, 0.0f,
     1.0f, 1.0f,
     0.0f, 1.0f,
    // front face: counter clockwise 
     0.0f, 0.0f,
     1.0f, 0.0f,
     1.0f, 1.0f,
     0.0f, 1.0f,
    // left face: counter clockwise
     0.0f, 0.0f,
     1.0f, 0.0f,
     1.0f, 1.0f,
     0.0f, 1.0f,
    // right face: counter clockwise
     0.0f, 0.0f,
     1.0f, 0.0f,
     1.0f, 1.0f,
     0.0f, 1.0f,
    // botton face: counter clockwise 
     0.0f, 0.0f,
     1.0f, 0.0f,
     1.0f, 1.0f,
     0.0f, 1.0f,
    // top face: counter clockwise
     0.0f, 0.0f,
     1.0f, 0.0f,
     1.0f, 1.0f,
     0.0f, 1.0f,
  };
  float tangents[] = {
    // back face: counter clockwise 
    -1.0f, 0.0f, 0.0f,
    -1.0f, 0.0f, 0.0f,
    -1.0f, 0.0f, 0.0f,
    -1.0f, 0.0f, 0.0f,
    // front face: counter clockwise 
     1.0f, 0.0f, 0.0f,
     1.0f, 0.0f, 0.0f,
     1.0f, 0.0f, 0.0f,
     1.0f, 0.0f, 0.0f,
    // left face: counter clockwise
     0.0f, 1.0f, 0.0f,
     0.0f, 1.0f, 0.0f,
     0.0f, 1.0f, 0.0f,
     0.0f, 1.0f, 0.0f,
    // right face: counter clockwise
     0.0f,-1.0f, 0.0f,
     0.0f,-1.0f, 0.0f,
     0.0f,-1.0f, 0.0f,
     0.0f,-1.0f, 0.0f,
    // botton face: counter clockwise 
    -1.0f, 0.0f, 0.0f,
    -1.0f, 0.0f, 0.0f,
    -1.0f, 0.0f, 0.0f,
    -1.0f, 0.0f, 0.0f,
    // top face: counter clockwise
     1.0f, 0.0f, 0.0f,
     1.0f, 0.0f, 0.0f,
     1.0f, 0.0f, 0.0f,
     1.0f, 0.0f, 0.0f,
  };
  unsigned int indices[] = {
    0,1,2,0,2,3,
    4,5,6,4,6,7,
    8,9,10,8,10,11,
    12,13,14,12,14,15,
    16,17,18,16,18,19,
    20,21,22,20,22,23
  };
  // create VAO
  glGenVertexArrays(1,&m_vao);
  glBindVertexArray(m_vao);
  // create coord buffer
  GLuint id[4];   // buffers: coord, normal, tangent, texcoord
  glGenBuffers(4,id);
  glBindBuffer(GL_ARRAY_BUFFER,id[0]);
  glBufferData(GL_ARRAY_BUFFER,sizeof(coords),coords,GL_STATIC_DRAW);
  glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,0,0);
  glEnableVertexAttribArray(0);
  // create normal buffer
  glBindBuffer(GL_ARRAY_BUFFER,id[1]);
  glBufferData(GL_ARRAY_BUFFER,sizeof(normals),normals,GL_STATIC_DRAW);
  glVertexAttribPointer(1,3,GL_FLOAT,GL_FALSE,0,0);
  glEnableVertexAttribArray(1);
  // create tangent buffer
  glBindBuffer(GL_ARRAY_BUFFER,id[2]);
  glBufferData(GL_ARRAY_BUFFER,sizeof(tangents),tangents,GL_STATIC_DRAW);
  glVertexAttribPointer(2,3,GL_FLOAT,GL_FALSE,0,0);
  glEnableVertexAttribArray(2);
  // create tex coord buffer
  glBindBuffer(GL_ARRAY_BUFFER,id[3]);
  glBufferData(GL_ARRAY_BUFFER,sizeof(normals),texcoords,GL_STATIC_DRAW);
  glVertexAttribPointer(3,2,GL_FLOAT,GL_FALSE,0,0);
  glEnableVertexAttribArray(3);
  // create index buffer
  GLuint index;
  glGenBuffers(1,&index);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,index);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER,sizeof(indices),indices,GL_STATIC_DRAW);
}

Cube::~Cube () 
{
}

void Cube::Draw (StatePtr )
{
  glBindVertexArray(m_vao);
  glDrawElements(GL_TRIANGLES,36,GL_UNSIGNED_INT,0);
}