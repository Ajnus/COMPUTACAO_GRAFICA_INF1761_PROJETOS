#include <memory>
class Camera;
using CameraPtr = std::shared_ptr<Camera>; 

#ifndef CAMERA_H
#define CAMERA_H

#include "state.h"

#include <glm/glm.hpp>

class Camera {
public:
  virtual glm::mat4 GetProjMatrix () const {
    return glm::mat4(1.0f);
  }
  virtual glm::mat4 GetViewMatrix () const {
    return glm::mat4(1.0f);
  }
  virtual void Load (StatePtr) const {
  }
};

#endif