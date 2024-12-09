#include "shader.h"
#include "state.h"

#include "glad.h"
#include <GLFW/glfw3.h>
#include <glm/gtc/type_ptr.hpp>

#include <fstream>
#include <iostream>
#include <sstream> 
#include <cstdlib>

// read file content to a string
static std::string ReadFile (const std::string& filename) 
{
  std::ifstream fp;
  fp.open(filename); 
  if (!fp.is_open()) {
    std::cerr << "Could not open file: " << filename << std::endl;
    exit(1);
  } 
  std::stringstream strStream;
  strStream << fp.rdbuf(); //read the file
  return strStream.str(); //str holds the content of the file
}

static void CompileShader (const std::string& filename, GLuint id)
{
  GLint status;
  glCompileShader(id);
  glGetShaderiv(id, GL_COMPILE_STATUS, &status);
  if (!status) {
     GLint len;
     glGetShaderiv(id, GL_INFO_LOG_LENGTH, &len);
     char* message = new char[len];
     glGetShaderInfoLog(id, len, 0, message);
     std::cerr << filename << ":" << std::endl << message << std::endl;
     delete [] message;
     exit(1);
   }
}

static GLuint CreateShader (GLenum shadertype, const std::string& filename)
{
  GLuint id = glCreateShader(shadertype);
  if (id==0) {
    std::cerr << "Could not create shader object";
    exit(1);
  }
  std::string source = ReadFile(filename);
  const char* csource = source.c_str();
  glShaderSource(id, 1, &csource, 0);
  CompileShader(filename,id);
  return id;
}

////////////////////////////

ShaderPtr Shader::Make ()
{
  return ShaderPtr(new Shader());
}

Shader::Shader ()
: m_texunit(0)
{
  m_pid = glCreateProgram();
  if (m_pid==0) {
    std::cerr << "Could not create shader object";
    exit(1);
  }
}

Shader::~Shader ()
{
}

void Shader::AttachVertexShader (const std::string& filename)
{
  GLuint sid = CreateShader(GL_VERTEX_SHADER,filename);
  glAttachShader(m_pid,sid);
}
void Shader::AttachFragmentShader (const std::string& filename)
{
  GLuint sid = CreateShader(GL_FRAGMENT_SHADER,filename);
  glAttachShader(m_pid,sid);
}
void Shader::AttachGeometryShader (const std::string& filename)
{
  GLuint sid = CreateShader(GL_GEOMETRY_SHADER,filename);
  glAttachShader(m_pid,sid);
}
void Shader::AttachTesselationShader (const std::string& control, const std::string& evaluation)
{
  GLuint cid = CreateShader(GL_TESS_CONTROL_SHADER,control);
  glAttachShader(m_pid,cid);
  GLuint eid = CreateShader(GL_TESS_EVALUATION_SHADER,evaluation);
  glAttachShader(m_pid,eid);
}

void Shader::Link ()
{
  GLint status;
  glLinkProgram(m_pid);
  glGetProgramiv(m_pid, GL_LINK_STATUS, &status);
  if (!status) {
    GLint len;
    glGetProgramiv(m_pid, GL_INFO_LOG_LENGTH, &len);
    char* message = new char[len];
    glGetProgramInfoLog(m_pid, len, 0, message);
    std::cerr << message << std::endl;
    delete [] message;
    exit(1);
  }
}  

void Shader::UseProgram () const
{
  glUseProgram(m_pid);
}


void Shader::SetUniform (const std::string& varname, int x) const
{
  GLint loc = glGetUniformLocation(m_pid,varname.c_str());
  glUniform1i(loc,x);
}

void Shader::SetUniform (const std::string& varname, float x) const
{
  GLint loc = glGetUniformLocation(m_pid,varname.c_str());
  glUniform1f(loc,x);
}

void Shader::SetUniform (const std::string& varname, const glm::vec3& vet) const
{
  GLint loc = glGetUniformLocation(m_pid,varname.c_str());
  glUniform3fv(loc,1,glm::value_ptr(vet));
}

void Shader::SetUniform (const std::string& varname, const glm::vec4& vet) const
{
  GLint loc = glGetUniformLocation(m_pid,varname.c_str());
  glUniform4fv(loc,1,glm::value_ptr(vet));
}

void Shader::SetUniform (const std::string& varname, const glm::mat4& mat) const
{
  GLint loc = glGetUniformLocation(m_pid,varname.c_str());
  glUniformMatrix4fv(loc,1,GL_FALSE,glm::value_ptr(mat));
}

void Shader::SetUniform (const std::string& varname, const std::vector<int>& x) const
{
  GLint loc = glGetUniformLocation(m_pid,varname.c_str());
  glUniform1iv(loc,x.size(),x.data());
}

void Shader::SetUniform (const std::string& varname, const std::vector<float>& x) const
{
  GLint loc = glGetUniformLocation(m_pid,varname.c_str());
  glUniform1fv(loc,x.size(),x.data());
}

void Shader::SetUniform (const std::string& varname, const std::vector<glm::vec3>& vet) const
{
  GLint loc = glGetUniformLocation(m_pid,varname.c_str());
  glUniform3fv(loc,vet.size(),(float*)vet.data());
}

void Shader::SetUniform (const std::string& varname, const std::vector<glm::vec4>& vet) const
{
  GLint loc = glGetUniformLocation(m_pid,varname.c_str());
  glUniform4fv(loc,vet.size(),(float*)vet.data());
}

void Shader::SetUniform (const std::string& varname, const std::vector<glm::mat4>& mat) const
{
  GLint loc = glGetUniformLocation(m_pid,varname.c_str());
  glUniformMatrix4fv(loc,mat.size(),GL_FALSE,(float*)mat.data());
}

void Shader::ActiveTexture (const std::string& varname)
{
  SetUniform(varname,m_texunit);
  glActiveTexture(GL_TEXTURE0+m_texunit);
  m_texunit++;
}

void Shader::DeactiveTexture ()
{
  m_texunit--;
}

void Shader::Load (StatePtr st)
{
  st->PushShader(shared_from_this());
}

void Shader::Unload (StatePtr st)
{
  st->PopShader();
}