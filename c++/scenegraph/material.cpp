#include "material.h"
#include "shader.h"
#include "state.h"


#include "glad/glad.h"
#include <GLFW/glfw3.h>

MaterialPtr Material::Make (float r, float g, float b, float opacity)
{
  return MaterialPtr(new Material(r,g,b,opacity));
}

Material::Material (float r, float g, float b, float opacity)
: m_amb(r,g,b,1.0f), 
  m_dif(r,g,b,1.0f), 
  m_spe(1.0f,1.0f,1.0f,1.0f), 
  m_shi(32.0f),
  m_opacity(opacity)
{
}
Material::~Material ()
{
}
void Material::SetAmbient (float r, float g, float b)
{
  m_amb[0] = r;
  m_amb[1] = g;
  m_amb[2] = b;
}
void Material::SetDiffuse (float r, float g, float b)
{
  m_dif[0] = r;
  m_dif[1] = g;
  m_dif[2] = b;
}
void Material::SetSpecular (float r, float g, float b)
{
  m_spe[0] = r;
  m_spe[1] = g;
  m_spe[2] = b;
  m_spe[3] = 0.0f;
}
void Material::SetShininess (float shi)
{
  m_shi = shi;
}
void Material::SetOpacity (float opacity)
{
  m_opacity = opacity;
}
void Material::Load (StatePtr st)
{
  ShaderPtr shd = st->GetShader();
  shd->SetUniform("mamb",m_amb);
  shd->SetUniform("mdif",m_dif);
  shd->SetUniform("mspe",m_spe);
  shd->SetUniform("mshi",m_shi);
  shd->SetUniform("mopacity",m_opacity);
}
