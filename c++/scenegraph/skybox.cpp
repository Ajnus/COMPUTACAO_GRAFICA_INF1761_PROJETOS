#include "skybox.h"
#include "error.h"


#include "glad/glad.h"
#include <GLFW/glfw3.h>

#include <glm/gtc/matrix_transform.hpp>

SkyBoxPtr SkyBox::Make ()
{
  return SkyBoxPtr(new SkyBox());
}

SkyBox::SkyBox ()
{
  float coords[] = { 
    -1.0f,  1.0f, -1.0f,
    -1.0f, -1.0f, -1.0f,
     1.0f, -1.0f, -1.0f,
     1.0f, -1.0f, -1.0f,
     1.0f,  1.0f, -1.0f,
    -1.0f,  1.0f, -1.0f,

    -1.0f, -1.0f,  1.0f,
    -1.0f, -1.0f, -1.0f,
    -1.0f,  1.0f, -1.0f,
    -1.0f,  1.0f, -1.0f,
    -1.0f,  1.0f,  1.0f,
    -1.0f, -1.0f,  1.0f,

     1.0f, -1.0f, -1.0f,
     1.0f, -1.0f,  1.0f,
     1.0f,  1.0f,  1.0f,
     1.0f,  1.0f,  1.0f,
     1.0f,  1.0f, -1.0f,
     1.0f, -1.0f, -1.0f,

    -1.0f, -1.0f,  1.0f,
    -1.0f,  1.0f,  1.0f,
     1.0f,  1.0f,  1.0f,
     1.0f,  1.0f,  1.0f,
     1.0f, -1.0f,  1.0f,
    -1.0f, -1.0f,  1.0f,

    -1.0f,  1.0f, -1.0f,
     1.0f,  1.0f, -1.0f,
     1.0f,  1.0f,  1.0f,
     1.0f,  1.0f,  1.0f,
    -1.0f,  1.0f,  1.0f,
    -1.0f,  1.0f, -1.0f,

    -1.0f, -1.0f, -1.0f,
    -1.0f, -1.0f,  1.0f,
     1.0f, -1.0f, -1.0f,
     1.0f, -1.0f, -1.0f,
    -1.0f, -1.0f,  1.0f,
     1.0f, -1.0f,  1.0f
  };
  // create VAO
  glGenVertexArrays(1,&m_vao);
  glBindVertexArray(m_vao);
  // create coord and normal buffer
  glGenBuffers(1,&m_coord_buffer);
  glBindBuffer(GL_ARRAY_BUFFER,m_coord_buffer);
  glBufferData(GL_ARRAY_BUFFER,sizeof(coords),coords,GL_STATIC_DRAW);
  glVertexAttribPointer(LOC::COORD,3,GL_FLOAT,GL_FALSE,0,0);
}

SkyBox::~SkyBox () 
{
}

void SkyBox::Draw (StatePtr st)
{ 
  // draw at camera position
  CameraPtr camera = st->GetCamera();
  glm::vec4 origin = glm::vec4(0.0f,0.0f,0.0f,1.0f);
  glm::vec3 peye = glm::vec3(glm::inverse(camera->GetViewMatrix()) * origin);
  glm::mat4 m = glm::translate(glm::mat4(1.0f),peye);
  st->PushMatrix();
  st->LoadMatrix(m);
  st->LoadMatrices();    // update loaded matrices
  glDepthMask(GL_FALSE);
  glBindVertexArray(m_vao);
  glBindBuffer(GL_ARRAY_BUFFER,m_coord_buffer);
  glEnableVertexAttribArray(LOC::COORD); 
  glDrawArrays(GL_TRIANGLES,0,36);
  glBindBuffer(GL_ARRAY_BUFFER,m_coord_buffer);
  glDisableVertexAttribArray(LOC::COORD); 
  glDepthMask(GL_TRUE);
  st->PopMatrix();
}