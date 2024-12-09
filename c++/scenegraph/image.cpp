#include "image.h"

#define STB_IMAGE_IMPLEMENTATION
#include <stb/stb_image.h>

#include <iostream>
#include <cstdlib>

Image::Image (const std::string& filename)
{
  stbi_set_flip_vertically_on_load(true);
  m_data = stbi_load(filename.c_str(),&m_width,&m_height,&m_nchannels,0); 
  if (!m_data) {
    std::cerr << "Could not load image: " << filename << std::endl;
    exit(1);
  }
}

ImagePtr Image::Make (const std::string& filename)
{
  return ImagePtr(new Image(filename));
}

Image::~Image ()
{
  stbi_image_free(m_data);
}

const unsigned char* Image::GetData () const
{
  return m_data;
}

int Image::GetWidth () const
{
  return m_width;
}

int Image::GetHeight () const
{
  return m_height;
}

int Image::GetNChannels () const
{
  return m_nchannels;
}

void Image::ExtractSubimage (int x, int y, int w, int h, unsigned char* img)
{
  for (int i=0; i<h; ++i) {
    memcpy(img+((h-i-1)*w)*m_nchannels,m_data+((y+i)*m_width+x)*m_nchannels,w*m_nchannels); 
  }
}