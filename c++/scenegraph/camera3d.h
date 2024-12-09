#include <memory>
class Camera3D;
using Camera3DPtr = std::shared_ptr<Camera3D>; 

#ifndef CAMERA_3D_H
#define CAMERA_3D_H

#include "camera.h"
#include "node.h"
#include "arcball.h"
#include <glm/glm.hpp>

class Camera3D : public Camera {
  bool m_ortho;
  float m_fovy;
  float m_znear, m_zfar;
  glm::vec3 m_center;   
  glm::vec3 m_eye;   
  glm::vec3 m_up;   
  ArcballPtr m_arcball;
  NodePtr m_reference;   // reference frame
protected:
  Camera3D (float x, float y, float z);
public:
  static Camera3DPtr Make (float x, float y, float z);
  virtual ~Camera3D ();
  void SetAngle (float fovy);
  void SetZPlanes (float near, float far);
  void SetCenter (float x, float y, float z);
  void SetEye (float x, float y, float z);
  void SetUpDir (float x, float y, float z);
  void SetOrtho (bool ortho);
  ArcballPtr CreateArcball ();
  ArcballPtr GetArcball () const;
  glm::mat4 GetProjMatrix () const;
  glm::mat4 GetViewMatrix () const;
  void SetReference (NodePtr reference);
  virtual void Load (StatePtr st) const;
};

#endif