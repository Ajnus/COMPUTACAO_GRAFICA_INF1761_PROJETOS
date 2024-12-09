#include <memory>
class Camera;
using CameraPtr = std::shared_ptr<Camera>;

#ifndef CAMERA_H
#define CAMERA_H

#include "node.h"
#include <glm/glm.hpp>

class Camera
{
  float m_xmin, m_xmax, m_ymin, m_ymax;

protected:
  Camera(float xmin, float xmax, float ymin, float ymax);

public:
  static CameraPtr Make(float xxmin, float xmax, float ymin, float ymax);
  virtual ~Camera();
  glm::mat4 GetProjMatrix() const;
  glm::mat4 GetViewMatrix() const;
};
#endif