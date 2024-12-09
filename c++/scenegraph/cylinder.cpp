#include "cylinder.h"
#include "grid.h"
#include "error.h"
#include "disk.h"

#include <cmath>
#include <iostream>

#include "glad/glad.h"
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#define PI 3.14159265f

CylinderPtr Cylinder::Make(int nstack, int nslice, float radius, float height, float slope)
{
    return CylinderPtr(new Cylinder(nstack, nslice, radius, height, slope));
}

Cylinder::Cylinder(int nstack, int nslice, float radius, float height, float slope) : m_nslice(nslice), m_height(height), topCap(Disk::Make(nslice)),
                                                                         bottomCap(Disk::Make(nslice)) // Inicializa as tampas usando Disk
{
    // Gerar a grade para a malha do cilindro
    GridPtr grid = Grid::Make(nstack, m_nslice);
    m_nind = grid->IndexCount();

    // Alocar coordenadas, tangentes e texcoord
    float *coord = new float[3 * (nstack + 1) * (m_nslice + 1)];
    float *tangent = new float[3 * (nstack + 1) * (m_nslice + 1)];
    float *texcoord = new float[2 * (nstack + 1) * (m_nslice + 1)];
    // const float* texcoord = grid->GetCoords();

    // Tampas
    // DiskPtr topCap = Disk::Make(m_nslice);
    // DiskPtr bottomCap = Disk::Make(m_nslice);

    int nc = 0;
    int nt = 0; // índice para texcoord
    for (int i = 0; i <= nstack; ++i)
    {
        float stackHeight = height * (float)i / (float)nstack;
        float currentRadius = radius - (slope * stackHeight / height);
        for (int j = 0; j <= m_nslice; ++j)
        {
            float theta = 2.0f * PI * (float)(m_nslice - j) / (float)m_nslice;
            float x = currentRadius * cos(theta);
            float z = currentRadius * sin(theta);

            // Armazenar coordenadas do cilindro
            coord[nc + 0] = x;
            coord[nc + 1] = stackHeight;
            coord[nc + 2] = z;

            // Armazenar tangentes
            tangent[nc + 0] = cos(theta);
            tangent[nc + 1] = 0;
            tangent[nc + 2] = sin(theta);

            // Armazenar texcoord com índice separado
            texcoord[nt + 0] = (float)j / (float)m_nslice; // U
            texcoord[nt + 1] = (float)i / (float)nstack;   // V

            nc += 3; // para coordenadas e tangentes
            nt += 2; // para texcoord
        }
    }

    // Criar VAO
    glGenVertexArrays(1, &m_vao);
    glBindVertexArray(m_vao);

    // Criar buffers
    GLuint id[3]; // buffers: coord/normal, tangent, texcoord
    glGenBuffers(3, id);

    glBindBuffer(GL_ARRAY_BUFFER, id[0]);
    glBufferData(GL_ARRAY_BUFFER, 3 * grid->VertexCount() * sizeof(float), coord, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(1);

    glBindBuffer(GL_ARRAY_BUFFER, id[1]);
    glBufferData(GL_ARRAY_BUFFER, 3 * grid->VertexCount() * sizeof(float), tangent, GL_STATIC_DRAW);
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(2);

    glBindBuffer(GL_ARRAY_BUFFER, id[2]);
    glBufferData(GL_ARRAY_BUFFER, 2 * grid->VertexCount() * sizeof(float), texcoord, GL_STATIC_DRAW);
    glVertexAttribPointer(3, 2, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(3);

    // Criar o buffer de índices
    GLuint index;
    glGenBuffers(1, &index);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, index);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_nind * sizeof(unsigned int), grid->GetIndices(), GL_STATIC_DRAW);

    // Criar tampas
    float *capCoord = new float[3 * (m_nslice + 1) * 2];
    float *capTexcoord = new float[2 * (m_nslice + 1) * 2];
    unsigned int *capIndices = new unsigned int[3 * m_nslice * 2];

    // Coordenadas para a tampa superior
    for (int j = 0; j <= m_nslice; ++j)
    {
        float theta = 2.0f * PI * (float)j / (float)m_nslice;
        capCoord[j * 3 + 0] = radius * cos(theta); // x
        capCoord[j * 3 + 1] = height;              // y (tampa superior)
        capCoord[j * 3 + 2] = radius * sin(theta); // z

        // Texcoord para a tampa superior
        capTexcoord[j * 2 + 0] = (float)j / (float)m_nslice; // U
        capTexcoord[j * 2 + 1] = 1.0f;                       // V (tampa superior)
    }

    // Coordenadas para a tampa inferior
    for (int j = 0; j <= m_nslice; ++j)
    {
        float theta = 2.0f * PI * (float)j / (float)m_nslice;
        capCoord[(m_nslice + 1 + j) * 3 + 0] = radius * cos(theta); // x
        capCoord[(m_nslice + 1 + j) * 3 + 1] = 0.0f;                // y (tampa inferior)
        capCoord[(m_nslice + 1 + j) * 3 + 2] = radius * sin(theta); // z

        // Texcoord para a tampa inferior
        capTexcoord[(m_nslice + 1 + j) * 2 + 0] = (float)j / (float)m_nslice; // U
        capTexcoord[(m_nslice + 1 + j) * 2 + 1] = 0.0f;                       // V (tampa inferior)
    }

    // Gerar índices para as tampas
    for (int j = 0; j < m_nslice; ++j)
    {
        // Tampa superior
        capIndices[j * 3 + 0] = 0;                            // Centro da tampa superior
        capIndices[j * 3 + 1] = j + 1;                        // Ponto j
        capIndices[j * 3 + 2] = j + 2 > m_nslice ? 1 : j + 2; // Próximo ponto
    }

    for (int j = 0; j < m_nslice; ++j)
    {
        // Tampa inferior
        capIndices[(m_nslice + j) * 3 + 0] = m_nslice + 1;                                                                            // Centro da tampa inferior
        capIndices[(m_nslice + j) * 3 + 1] = m_nslice + 2 + j;                                                                        // Ponto j na tampa inferior
        capIndices[(m_nslice + j) * 3 + 2] = m_nslice + 2 + (j + 1) > (2 * m_nslice + 1) ? (m_nslice + 2) : (m_nslice + 2 + (j + 1)); // Próximo ponto
    }
    // Criar buffer para as tampas
    glGenVertexArrays(1, &m_capVao);
    glBindVertexArray(m_capVao);

    GLuint capVBO[2]; // VBOs para coordenadas e texcoord
    glGenBuffers(2, capVBO);

    // Coordenadas da tampa
    glBindBuffer(GL_ARRAY_BUFFER, capVBO[0]);
    glBufferData(GL_ARRAY_BUFFER, 3 * (m_nslice + 1) * 2 * sizeof(float), capCoord, GL_STATIC_DRAW);
    glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(3);

    // Texcoord da tampa
    glBindBuffer(GL_ARRAY_BUFFER, capVBO[1]);
    glBufferData(GL_ARRAY_BUFFER, 2 * (m_nslice + 1) * 2 * sizeof(float), capTexcoord, GL_STATIC_DRAW);
    glVertexAttribPointer(4, 2, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(4);

    // Índices para as tampas
    GLuint capIndex;
    glGenBuffers(1, &capIndex);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, capIndex);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, 3 * m_nslice * 2 * sizeof(unsigned int), capIndices, GL_STATIC_DRAW);

    // Limpar memória

    delete[] tangent;
    delete[] coord;
    delete[] texcoord;

    delete[] capCoord;
    delete[] capTexcoord;
    delete[] capIndices;

    // Configurar a tampa superior
    /*
    topCap = Disk::Make(m_nslice);
    m_topTransform = Transform::Make();
    m_topTransform->LoadIdentity();
    m_topTransform->Translate(0.0f, m_height, 0.0f);
    m_topTransform->Rotate(90.0f, 1.0f, 0.0f, 0.0f);
    */

    /*
    for (int i = 0; i < m_nslice; ++i)
    {
        // Calcula a posição rotacionada no eixo X para ficar alinhada com o cilindro
        float theta = 2 * PI * i / m_nslice;
        topCap->coord[3 * i + 0] = radius * cos(theta);
        topCap->coord[3 * i + 1] = height; // altura da tampa superior
        topCap->coord[3 * i + 2] = radius * sin(theta);
    }
    */

    // Configurar a tampa inferior

    /*
    bottomCap = Disk::Make(m_nslice);
    m_bottomTransform = Transform::Make();
    m_bottomTransform->LoadIdentity();
    m_bottomTransform->Translate(0.0f, 0.0f, 0.0f);
    m_bottomTransform->Rotate(90.0f, 1.0f, 0.0f, 0.0f);
    */

    /*
    for (int i = 0; i < m_nslice; ++i)
    {
        float theta = 2 * PI * i / m_nslice;
        bottomCap->coord[3 * i + 0] = radius * cos(theta);
        bottomCap->coord[3 * i + 1] = 0.0f; // nível da base
        bottomCap->coord[3 * i + 2] = radius * sin(theta);
    }
    */

    // Unbind VAOs
    // glBindVertexArray(0);
}

Cylinder::~Cylinder()
{
    // glDeleteBuffers(1, &m_vbo);
    // glDeleteBuffers(1, &m_ebo);
    // glDeleteVertexArrays(1, &m_vao);
}

void Cylinder::Draw(StatePtr st)
{
    glEnable(GL_DEPTH_TEST);
    glDisable(GL_BLEND);
    glDepthMask(GL_TRUE); // Ensure depth writing is enabled

    // Desenhar o corpo do cilindro
    glBindVertexArray(m_vao);
    glDrawElements(GL_TRIANGLES, m_nind, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0); // Unbind após desenhar

    // glBindVertexArray(m_capVao);
    // glDrawElements(GL_TRIANGLES, m_nind, GL_UNSIGNED_INT, 0);
    // glBindVertexArray(0); // Unbind após desenhar

    // Aplicar transformações para as tampas
    // m_topTransform->Load(st);   // Carregar transformação da tampa superior
    // topCap->Draw(st);           // Desenhar a tampa superior
    // m_topTransform->Unload(st); // Reverter transformação

    // m_bottomTransform->Load(st);   // Carregar transformação da tampa inferior
    // bottomCap->Draw(st);           // Desenhar a tampa inferior
    // m_bottomTransform->Unload(st); // Reverter transformação

    // Posicionar e desenhar a tampa superior
    // glPushMatrix();
    // glTranslatef(0.0f, m_height, 0.0f);
    // glRotatef(90.0f, 1.0f, 0.0f, 0.0f); // Rotacionar 90 graus em torno do eixo X
    // topCap->Draw(st); // *** TRANSFORM NA MAIN ***
    // glPopMatrix();

    // Posicionar e desenhar a tampa inferior
    // glPushMatrix();
    // glTranslatef(0.0f, 0.0f, 0.0f);
    // glRotatef(90.0f, 1.0f, 0.0f, 0.0f); // Rotacionar 90 graus em torno do eixo X
    //          bottomCap->Draw(st); // *** TRANSFORM NA MAIN ***
    // glPopMatrix();

    // Desenha as tampas já com as coordenadas configuradas
    // topCap->Draw(st);
    // bottomCap->Draw(st);

    // Desenhar as tampas
    // glBindVertexArray(m_capVao);
    // glDrawElements(GL_TRIANGLES, 3 * m_nslice * 2, GL_UNSIGNED_INT, 0);

    // Desvincular o VAO
    // glBindVertexArray(0);

    // --- //

    /*

     // Desenhar o corpo do cilindro
    glBindVertexArray(m_vao);
    glDrawElements(GL_TRIANGLES, m_nind, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0); // Unbind após desenhar

    // Matrizes de transformação para as tampas
    glm::mat4 topCapTransform = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, m_height, 0.0f));
    topCapTransform = glm::rotate(topCapTransform, glm::radians(90.0f), glm::vec3(1.0f, 0.0f, 0.0f));

    glm::mat4 bottomCapTransform = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.0f));
    bottomCapTransform = glm::rotate(bottomCapTransform, glm::radians(90.0f), glm::vec3(1.0f, 0.0f, 0.0f));

    // Passa a matriz de transformação para o shader e desenha as tampas
    st->SetModelMatrix(topCapTransform);
    topCap->Draw(st);

    st->SetModelMatrix(bottomCapTransform);
    bottomCap->Draw(st);

        */

    // --- //
    /*

    // Desenhar o corpo do cilindro
    glm::mat4 modelMatrix = glm::mat4(1.0f);
    st->SetUniform("uModelMatrix", modelMatrix); // Passa a matriz identidade para o corpo
    glBindVertexArray(m_vao);
    glDrawElements(GL_TRIANGLES, m_nind, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);

    // Posicionar e desenhar a tampa superior
    modelMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, m_height, 0.0f));
    modelMatrix = glm::rotate(modelMatrix, glm::radians(90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
    st->SetUniform("uModelMatrix", modelMatrix);
    topCap->Draw(st);

    // Posicionar e desenhar a tampa inferior
    modelMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.0f));
    modelMatrix = glm::rotate(modelMatrix, glm::radians(90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
    st->SetUniform("uModelMatrix", modelMatrix);
    bottomCap->Draw(st);
    */
}
