#include "disk.h"

#include <iostream>
#include "glad.h"
#include <vector>
#include <glm/fwd.hpp>
#include <glm/trigonometric.hpp>

DiskPtr Disk::Make(int numVertex)
{
    return DiskPtr(new Disk(numVertex));
}

Disk::Disk(int numVertex)
{
    std::vector<glm::vec3> coord;
    std::vector<glm::vec2> texcoord;
    float angle = 2.0f * 3.1415f / numVertex;

    std::vector<glm::vec3> temp;

    temp.push_back(glm::vec3(0.0f, 0.0f, 0.0f));
    texcoord.push_back(glm::vec2(0.5f, 0.5f));

    // achar coordenadas
    for (int i = 0; i < numVertex; i++)
    {
        float currentAngle = angle * i;
        float x = cos(currentAngle);
        float y = sin(currentAngle);
        float z = 0.0f;

        temp.push_back(glm::vec3(x, y, z));

        float u = x * 0.5f + 0.5f;
        float v = y * 0.5f + 0.5f;

        texcoord.push_back(glm::vec2(u, v));
        texcoord.push_back(glm::vec2(u, v));
        texcoord.push_back(glm::vec2(u, v));
    }

    for (int i = 1; i < numVertex; i++)
    {
        coord.push_back(temp[0]);
        coord.push_back(temp[i]);
        coord.push_back(temp[i + 1]);
    }

    coord.push_back(temp[0]);
    coord.push_back(temp[numVertex]);
    coord.push_back(temp[1]);

    // VAO
    glGenVertexArrays(1, &m_vao);
    glBindVertexArray(m_vao);

    // coord buffer
    GLuint id;
    glGenBuffers(1, &id);
    glBindBuffer(GL_ARRAY_BUFFER, id);
    glBufferData(GL_ARRAY_BUFFER, coord.size() * sizeof(glm::vec3), &coord[0], GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0); // coord
    glEnableVertexAttribArray(0);

    // texcoord buffer
    GLuint texId;
    glGenBuffers(1, &texId);
    glBindBuffer(GL_ARRAY_BUFFER, texId);
    glBufferData(GL_ARRAY_BUFFER, texcoord.size() * sizeof(glm::vec2), &texcoord[0], GL_STATIC_DRAW);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, 0); // texcoord
    glEnableVertexAttribArray(1);
}

Disk::~Disk()
{
}

void Disk::Draw(StatePtr)
{
    glBindVertexArray(m_vao);
    glDrawArrays(GL_TRIANGLE_FAN, 0, 129 * 3);
}