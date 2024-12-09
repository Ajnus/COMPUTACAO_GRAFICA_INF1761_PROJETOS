#include "disk.h"

#include <iostream>
#include <cmath>

#define PI 3.14159265f


#include "glad/glad.h"
#include <GLFW/glfw3.h>

DiskPtr Disk::Make (int nslice)
{
  return DiskPtr(new Disk(nslice));
}

Disk::Disk (int nslice)
: m_nslice(nslice)
{
  // create coord buffer
  float* coord = new float[2*nslice];
  float* texcoord = new float[2*nslice];
  
  for (int i=0; i<nslice; ++i) {
    float theta = 2*PI*i/nslice;
    coord[2*i+0] = cos(theta);
    coord[2*i+1] = sin(theta);
    texcoord[2*i+0] = 0.5+0.5*cos(theta);
    texcoord[2*i+1] = 0.5+0.5*sin(theta);
  }
  // create VAO
  glGenVertexArrays(1,&m_vao);
  glBindVertexArray(m_vao);
  GLuint id[2];
  glGenBuffers(2,id);
  glBindBuffer(GL_ARRAY_BUFFER,id[0]);
  glBufferData(GL_ARRAY_BUFFER,2*nslice*sizeof(float),coord,GL_STATIC_DRAW);
  glVertexAttribPointer(0,2,GL_FLOAT,GL_FALSE,0,nullptr);
  glEnableVertexAttribArray(0);
  glBindBuffer(GL_ARRAY_BUFFER,id[1]);
  glBufferData(GL_ARRAY_BUFFER,2*nslice*sizeof(float),texcoord,GL_STATIC_DRAW);
  glVertexAttribPointer(1,2,GL_FLOAT,GL_FALSE,0,nullptr);
  glEnableVertexAttribArray(1);
}

Disk::~Disk () 
{
}

void Disk::Draw (StatePtr )
{
  glBindVertexArray(m_vao);
  //glBindTexture(GL_TEXTURE_2D, m_texture); // Ensure the texture is bound
  glDrawArrays(GL_TRIANGLE_FAN,0,m_nslice);
}
