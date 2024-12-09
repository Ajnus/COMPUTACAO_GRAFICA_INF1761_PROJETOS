#include "camera.h"
#include "node.h"
#include "state.h"
#include "transform.h"

#include <cmath>
#include <iostream>

#include "glad.h"
#include <GLFW/glfw3.h>

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/string_cast.hpp>

CameraPtr Camera::Make(float xmin, float xmax, float ymin, float ymax)
{
    return CameraPtr(new Camera(xmin, xmax, ymin, ymax));
}

Camera::Camera(float xmin, float xmax, float ymin, float ymax)
    : m_xmin(xmin),
      m_xmax(xmax),
      m_ymin(ymin),
      m_ymax(ymax)
{
}

Camera::~Camera()
{
}

glm::mat4 Camera::GetProjMatrix() const
{
    int viewport[4]; // viewport dimension: {x0, y0, w, h}
    glGetIntegerv(GL_VIEWPORT, viewport);
    float w = viewport[2];
    float h = viewport[3];
    float dx = m_xmax - m_xmin;
    float dy = m_ymax - m_ymin;
    float xmin, xmax, ymin, ymax;
    if (w / h > dx / dy)
    {
        float xc = (m_xmin + m_xmax) / 2;
        xmin = xc - dx / 2 * w / h;
        xmax = xc + dx / 2 * w / h;
        ymin = m_ymin;
        ymax = m_ymax;
    }
    else
    {
        float yc = (m_ymin + m_ymax) / 2;
        ymin = yc - dy / 2 * h / w;
        ymax = yc + dy / 2 * h / w;
        xmin = m_xmin;
        xmax = m_xmax;
    }
    return glm::ortho(xmin, xmax, ymin, ymax);
}

glm::mat4 Camera::GetViewMatrix() const
{
    return glm::mat4(1.0f);
}