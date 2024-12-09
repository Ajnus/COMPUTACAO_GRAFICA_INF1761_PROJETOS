#include "mesh.h"

#if _WIN32
#include <glad/glad.h>
#else

#include "glad/glad.h"
#include <GLFW/glfw3.h>
#endif

#include <iostream>
#include <fstream>
#include <vector>
#include <cstdlib>

MeshPtr Mesh::Make (const std::string& filename)
{
  return MeshPtr(new Mesh(filename));
}

MeshPtr Mesh::Make ()
{
  return MeshPtr(new Mesh());
}

Mesh::Mesh (const std::string& filename)
: m_nind(0)
{
  std::vector<float> coords;
  std::vector<float> normals;
  std::vector<unsigned int> indices;
  // read file
  std::fstream fp;
  fp.open(filename,std::ios::in);
  if (!fp) {
    std::cerr << "Could not open file: " << filename << std::endl;
    exit(1);
  }
  while (!fp.eof()) {
    char c;
    float x, y, z;
    unsigned int i, j, k;
    fp >> c;
    switch (c) {
      case 'V':
        fp >> x >> y >> z;
        coords.push_back(x);
        coords.push_back(y);
        coords.push_back(z);
      break;
      case 'N':
        fp >> x >> y >> z;
        normals.push_back(x);
        normals.push_back(y);
        normals.push_back(z);
      break;
      case 'T':
        fp >> i >> j >> k;
        indices.push_back(i);
        indices.push_back(j);
        indices.push_back(k);
      break;
    }
  }
  fp.close();
  m_nind = indices.size();

  // create VAO
  glGenVertexArrays(1,&m_vao);
  SetCoordBuffer(coords.size(),coords.data(),3,0);
  SetNormalBuffer(normals.size(),normals.data(),3,0);
  SetIndexBuffer(indices.size(),indices.data());
}

Mesh::Mesh () 
{
  glGenVertexArrays(1,&m_vao);
}

Mesh::~Mesh () 
{
}

void Mesh::SetCoordBuffer (int size, const float* data, int ncomp, int stride)
{
  glBindVertexArray(m_vao);
  // create coord buffer
  GLuint id;
  glGenBuffers(1,&id);
  glBindBuffer(GL_ARRAY_BUFFER,id);
  glBufferData(GL_ARRAY_BUFFER,size*sizeof(float),(void*)data,GL_STATIC_DRAW);
  glVertexAttribPointer(0,ncomp,GL_FLOAT,GL_FALSE,stride,0);
  glEnableVertexAttribArray(0);
}

void Mesh::SetNormalBuffer (int size, const float* data, int ncomp, int stride)
{
  glBindVertexArray(m_vao);
  // create coord buffer
  GLuint id;
  glGenBuffers(1,&id);
  glBindBuffer(GL_ARRAY_BUFFER,id);
  glBufferData(GL_ARRAY_BUFFER,size*sizeof(float),(void*)data,GL_STATIC_DRAW);
  glVertexAttribPointer(1,ncomp,GL_FLOAT,GL_FALSE,stride,0);
  glEnableVertexAttribArray(1);
}

void Mesh::SetTangentBuffer (int size, const float* data, int ncomp, int stride)
{
  glBindVertexArray(m_vao);
  // create coord buffer
  GLuint id;
  glGenBuffers(1,&id);
  glBindBuffer(GL_ARRAY_BUFFER,id);
  glBufferData(GL_ARRAY_BUFFER,size*sizeof(float),(void*)data,GL_STATIC_DRAW);
  glVertexAttribPointer(2,ncomp,GL_FLOAT,GL_FALSE,stride,0);
  glEnableVertexAttribArray(2);
}

void Mesh::SetTexCoordBuffer (int size, const float* data, int ncomp, int stride)
{
  glBindVertexArray(m_vao);
  // create coord buffer
  GLuint id;
  glGenBuffers(1,&id);
  glBindBuffer(GL_ARRAY_BUFFER,id);
  glBufferData(GL_ARRAY_BUFFER,size*sizeof(float),(void*)data,GL_STATIC_DRAW);
  glVertexAttribPointer(3,ncomp,GL_FLOAT,GL_FALSE,stride,0);
  glEnableVertexAttribArray(3);
}

void Mesh::SetIndexBuffer (int size, const unsigned int* data)
{
  glBindVertexArray(m_vao);
  GLuint id;
  glGenBuffers(1,&id);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,id);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER,size*sizeof(unsigned int),(void*)data,GL_STATIC_DRAW);
  m_nind = size;
}

void Mesh::Draw (StatePtr )
{
  glBindVertexArray(m_vao);
  glDrawElements(GL_TRIANGLES,m_nind,GL_UNSIGNED_INT,0);
}