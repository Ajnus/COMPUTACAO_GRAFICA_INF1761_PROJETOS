#include "framebuffer.h"
#include <iostream>


#include "glad/glad.h"
#include <GLFW/glfw3.h>
#include <cstdlib>

Framebuffer::Framebuffer (TexDepthPtr depth, std::initializer_list<TexturePtr> colors)
: m_depth(depth), m_colors(colors)
{
  glGenFramebuffers(1,&m_fbo);
  glBindFramebuffer(GL_FRAMEBUFFER,m_fbo);
  if (m_depth != nullptr)
    glFramebufferTexture(GL_FRAMEBUFFER,GL_DEPTH_ATTACHMENT,m_depth->GetTexId(),0);
  for (int i=0; i<m_colors.size(); ++i) {
    auto tex = m_colors[i]->GetTexId();
    glFramebufferTexture(GL_FRAMEBUFFER,GL_COLOR_ATTACHMENT0+i,tex,0);
  }
  if(glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) {
    std::cout << "Framebuffer not complete" << std::endl;
    exit(1);
  }
  glBindFramebuffer(GL_FRAMEBUFFER,0);
}

FramebufferPtr Framebuffer::Make (TexDepthPtr depth, std::initializer_list<TexturePtr> colors)
{
  return FramebufferPtr(new Framebuffer(depth,colors));
}

Framebuffer::~Framebuffer () 
{
}

TexDepthPtr Framebuffer::GetDepthTexture () const
{
  return m_depth;
}

TexturePtr Framebuffer::GetColorTexture (int i) const
{
  return m_colors[i];
}

void Framebuffer::Bind ()
{
  glBindFramebuffer(GL_FRAMEBUFFER,m_fbo);
  if (m_colors.empty()) {
    glDrawBuffer(GL_NONE);
  }
  else {
    std::vector<GLenum> buffers;
    for (int i=0; i<m_colors.size(); ++i)
      buffers.push_back(GL_COLOR_ATTACHMENT0+i);
    glDrawBuffers(m_colors.size(),buffers.data());
  }
}

void Framebuffer::Unbind ()
{
  glBindFramebuffer(GL_FRAMEBUFFER,0);
  glDrawBuffer(GL_BACK);
}