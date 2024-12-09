#include "texdepth.h"
#include "state.h"
#include "shader.h"
#include "error.h"


#include "glad/glad.h"
#include <GLFW/glfw3.h>

TexDepthPtr TexDepth::Make (const std::string& varname, int width, int height)
{
  return TexDepthPtr(new TexDepth(varname,width,height));
}

TexDepth::TexDepth (const std::string& varname, int width, int height)
: m_varname(varname),
  m_width(width), m_height(height)
{
  glGenTextures(1,&m_tex);
  glBindTexture(GL_TEXTURE_2D,m_tex);
  glTexImage2D(GL_TEXTURE_2D,0,GL_DEPTH_COMPONENT,m_width,m_height,0,
               GL_DEPTH_COMPONENT,GL_FLOAT,0);
  glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_CLAMP_TO_EDGE);	
  glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_CLAMP_TO_EDGE);
  glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
  glBindTexture(GL_TEXTURE_2D,0);
}

TexDepth::~TexDepth ()
{
}

unsigned int TexDepth::GetTexId () const
{
  return m_tex;
}

void TexDepth::SetCompareMode ()
{
  glBindTexture(GL_TEXTURE_2D,m_tex);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_COMPARE_FUNC, GL_LEQUAL);
  glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_COMPARE_MODE, GL_COMPARE_REF_TO_TEXTURE);
  glBindTexture(GL_TEXTURE_2D,0);
}

void TexDepth::Load (StatePtr st)
{
  ShaderPtr shd = st->GetShader();
  shd->ActiveTexture(m_varname.c_str());
  glBindTexture(GL_TEXTURE_2D,m_tex);
}

void TexDepth::Unload (StatePtr st)
{
  ShaderPtr shd = st->GetShader();
  shd->DeactiveTexture();
}