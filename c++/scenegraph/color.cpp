#include "color.h"
#include "shader.h"
#include "state.h"


#include "glad/glad.h"
#include <GLFW/glfw3.h>

ColorPtr Color::Make (float r, float g, float b, float a)
{
  return ColorPtr(new Color(r,g,b,a));
}

Color::Color (float r, float g, float b, float a)
: m_color(r,g,b,a)
{
}
Color::~Color ()
{
}
void Color::Load (StatePtr st)
{
  ShaderPtr shd = st->GetShader();
  shd->SetUniform("color",m_color);
}
