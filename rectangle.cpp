#include "rectangle.h"

#include <iostream>
#include "glad.h"
#include <vector>
#include <glm/fwd.hpp>
#include <glm/trigonometric.hpp>


RectanglePtr Rectangle::Make()
{
    return RectanglePtr(new Rectangle());
}

Rectangle::Rectangle()
{
    float vertices[] = {
        -1.0f,  1.0f, 0.0f, 0.0f, 1.0f, 
        -1.0f, -1.0f, 0.0f, 0.0f, 0.0f,  
         1.0f, -1.0f, 0.0f, 1.0f, 0.0f,   
         1.0f,  1.0f, 0.0f, 1.0f, 1.0f    
    };

    unsigned int indices[] = {
    0, 1, 3,   
    1, 2, 3    
    };

    // create VAO
    glGenVertexArrays(1, &m_vao);
    glBindVertexArray(m_vao);
    // create coord buffer
    GLuint id;
    glGenBuffers(1, &id);
    glBindBuffer(GL_ARRAY_BUFFER, id);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);  // coord
    glEnableVertexAttribArray(0);
    GLuint tex;
    glGenBuffers(1, &tex);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, tex);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
}

Rectangle::~Rectangle()
{
}

void Rectangle::Draw(StatePtr)
{
    glDepthMask(GL_FALSE);
    glBindVertexArray(m_vao);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    glDepthMask(GL_TRUE);
}