#include <memory>
class Framebuffer;
using FramebufferPtr = std::shared_ptr<Framebuffer>; 

#ifndef FRAMEBUFFER_H
#define FRAMEBUFFER_H

#include "texture.h"
#include "texdepth.h"
#include <vector>
#include <initializer_list>

class Framebuffer {
  unsigned int m_fbo;
  TexDepthPtr m_depth;
  std::vector<TexturePtr> m_colors;
protected:
  Framebuffer (TexDepthPtr depth, std::initializer_list<TexturePtr> colors);
public:
  static FramebufferPtr Make (TexDepthPtr depth, std::initializer_list<TexturePtr> colors={});
  ~Framebuffer ();
  TexDepthPtr GetDepthTexture () const;
  TexturePtr GetColorTexture (int i) const;
  void Bind ();
  void Unbind ();
};

#endif