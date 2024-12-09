#include <memory>
class TexDepth;
using TexDepthPtr = std::shared_ptr<TexDepth>; 

#ifndef TEXDEPTH_H
#define TEXDEPTH_H

#include "appearance.h"
#include <glm/glm.hpp>
#include <string>

class TexDepth : public Appearance {
  unsigned int m_tex;
  std::string m_varname;
  int m_width;
  int m_height;
protected:
  TexDepth (const std::string& varname, int width, int height);
public:
  static TexDepthPtr Make (const std::string& varname, int width, int height);
  virtual ~TexDepth ();
  unsigned int GetTexId () const;
  void SetCompareMode ();
  virtual void Load (StatePtr st);
  virtual void Unload (StatePtr st);
};

#endif