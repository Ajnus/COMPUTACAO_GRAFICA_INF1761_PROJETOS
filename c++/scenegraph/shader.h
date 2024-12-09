#include <memory>
class Shader;
using ShaderPtr = std::shared_ptr<Shader>; 

#ifndef SHADER_H
#define SHADER_H

#include "light.h"
#include <glm/glm.hpp>
#include <vector>
#include <string>

class Shader : public std::enable_shared_from_this<Shader> {
  unsigned int m_pid;
  int m_texunit;
  LightPtr m_light;
  std::string m_space;  // lighting space
protected:
  Shader (LightPtr light, const std::string& space);
public:
  static ShaderPtr Make (LightPtr light=nullptr, const std::string& space="camera");
  virtual ~Shader ();
  void AttachVertexShader (const std::string& filename);
  void AttachFragmentShader (const std::string& filename);
  void AttachGeometryShader (const std::string& filename);
  void AttachTesselationShader (const std::string& control, const std::string& evaluation);
  void Link ();
  LightPtr GetLight () const;
  const std::string& GetLightingSpace () const;
  void UseProgram () const;
  void SetUniform (const std::string& varname, int x) const;
  void SetUniform (const std::string& varname, float x) const;
  void SetUniform (const std::string& varname, const glm::vec3& vet) const;
  void SetUniform (const std::string& varname, const glm::vec4& vet) const;
  void SetUniform (const std::string& varname, const glm::mat4& mat) const;
  void SetUniform (const std::string& varname, const std::vector<int>& x) const;
  void SetUniform (const std::string& varname, const std::vector<float>& x) const;
  void SetUniform (const std::string& varname, const std::vector<glm::vec3>& vet) const;
  void SetUniform (const std::string& varname, const std::vector<glm::vec4>& vet) const;
  void SetUniform (const std::string& varname, const std::vector<glm::mat4>& mat) const;
  void ActiveTexture (const std::string& varname);
  void DeactiveTexture ();  
  void Load (StatePtr st);
  void Unload (StatePtr st);
};

#endif