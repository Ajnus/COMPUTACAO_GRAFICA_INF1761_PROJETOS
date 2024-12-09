#include <memory>
class Texture;
using TexturePtr = std::shared_ptr<Texture>; 

#ifndef TEXTURE_H
#define TEXTURE_H

#include "appearance.h"
#include <glm/glm.hpp>
#include <string>

class Texture : public Appearance {
  unsigned int m_tex;
  std::string m_varname;
protected:
  Texture (const std::string& varname, const std::string& filename);
  Texture (const std::string& varname, int width, int height);
  Texture (const std::string& varname, const glm::vec3& texel);
public:
  static TexturePtr Make (const std::string& varname, const std::string& filename);
  static TexturePtr Make (const std::string& varname, int width, int height);
  static TexturePtr Make (const std::string& varname, const glm::vec3& texel);
  virtual ~Texture ();
  unsigned int GetTexId () const;
  virtual void Load (StatePtr st);
  virtual void Unload (StatePtr st);
};

#endif