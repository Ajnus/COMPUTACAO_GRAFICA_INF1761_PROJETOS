#include <memory>

class Cylinder;
using CylinderPtr = std::shared_ptr<Cylinder>;

#ifndef CYLINDER_H
#define CYLINDER_H

#include "shape.h"
#include "disk.h"

class Cylinder : public Shape
{
    unsigned int m_vao; // Vertex Array Object
    unsigned int m_vbo; // Vertex Buffer Object
    unsigned int m_ebo; // Element Buffer Object
    int m_segments;     // Número de segmentos ao longo da circunferência
    int m_nind;         // Número de índices
    unsigned int m_capVao;
    int m_nslice;
    int m_height;
    DiskPtr topCap;
    DiskPtr bottomCap;
    TransformPtr m_topTransform;
    TransformPtr m_bottomTransform;
    


protected:
    Cylinder(int nstack, int nslice, float radius, float height, float slope);
    //void GenerateCaps(float radius, float height, int nslice);

public:
    static CylinderPtr Make(int nstack = 64, int nslice = 64, float radius = 1.0f, float height = 2.0f, float slope = 0.0f);
    //(int segments = 32, float radius = 1.0f, float height = 2.0f);
    virtual ~Cylinder();
    virtual void Draw(StatePtr st);
};

#endif
