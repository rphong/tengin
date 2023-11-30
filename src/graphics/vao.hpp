#pragma once

#include <glad/glad.h>
#include "buffer.hpp"

#include <numeric>

class VAO {
   public:
    VAO(VBO&& vbo, EBO&& ebo);
    ~VAO();
    VAO(const VAO&) = delete;
    VAO& operator=(const VAO&) = delete;
    VAO(VAO&& other);
    VAO& operator=(VAO&& other);

    void setVertexBuffer();
    void setElementBuffer();
    void bind() const;

   private:
    void release();
    GLuint m_id;
    VBO m_vbo;
    EBO m_ebo;
};