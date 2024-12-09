#include "texture.h"
#include "image.h"
#include "state.h"

#include <glm/gtc/type_ptr.hpp>

#include "glad/glad.h"
#include <GLFW/glfw3.h>

#include <iostream>

TexturePtr Texture::Make (const std::string& varname, const std::string& filename)
{
  return TexturePtr(new Texture(varname,filename));
}
TexturePtr Texture::Make (const std::string& varname, int width, int height)
{
  return TexturePtr(new Texture(varname,width,height));
}
TexturePtr Texture::Make (const std::string& varname, const glm::vec3& texel)
{
  return TexturePtr(new Texture(varname,texel));
}

Texture::Texture (const std::string& varname, const std::string& filename)
: m_varname(varname)
{
  ImagePtr img = Image::Make(filename);
  glGenTextures(1,&m_tex);
  glBindTexture(GL_TEXTURE_2D,m_tex);
  glTexImage2D(GL_TEXTURE_2D,0,img->GetNChannels()==3?GL_RGB:GL_RGBA,
               img->GetWidth(),img->GetHeight(),0,
               img->GetNChannels()==3?GL_RGB:GL_RGBA,
               GL_UNSIGNED_BYTE,img->GetData());
  glGenerateMipmap(GL_TEXTURE_2D);
  glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_REPEAT);	
  glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR_MIPMAP_LINEAR);
  glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
  glBindTexture(GL_TEXTURE_2D,0);
}

Texture::Texture (const std::string& varname, int width, int height)
: m_varname(varname)
{
  glGenTextures(1,&m_tex);
  glBindTexture(GL_TEXTURE_2D,m_tex);
  glTexImage2D(GL_TEXTURE_2D,0,GL_RGB,width,height,0,
               GL_RGB,GL_UNSIGNED_BYTE,0);
  glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_REPEAT);	
  glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
  glBindTexture(GL_TEXTURE_2D,0);
}

Texture::Texture (const std::string& varname, const glm::vec3& texel)
: m_varname(varname)
{
  unsigned char color[3] = {
    (unsigned char)(texel[0]*255),
    (unsigned char)(texel[1]*255),
    (unsigned char)(texel[2]*255),
  };
  glGenTextures(1,&m_tex);
  glBindTexture(GL_TEXTURE_2D,m_tex);
  glTexImage2D(GL_TEXTURE_2D,0,GL_RGB,1,1,0,GL_RGB,GL_UNSIGNED_BYTE,color);
  glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_REPEAT);	
  glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
  glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
  glBindTexture(GL_TEXTURE_2D,0);
}


Texture::~Texture ()
{
}

unsigned int Texture::GetTexId () const
{
  return m_tex;
}

void Texture::Load (StatePtr st)
{
  ShaderPtr shd = st->GetShader();
  shd->ActiveTexture(m_varname.c_str());
  glBindTexture(GL_TEXTURE_2D,m_tex);
}

void Texture::Unload (StatePtr st)
{
  ShaderPtr shd = st->GetShader();
  shd->DeactiveTexture();
}
