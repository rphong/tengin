#pragma once

#include <glad/glad.h>

#include <optional>
#include "buffer.hpp"

namespace Graphics {
class VAO {
   public:
    VAO(VBO&& vbo);
    VAO(VBO&& vbo, EBO&& ebo);
    ~VAO();
    VAO(const VAO&) = delete;
    VAO& operator=(const VAO&) = delete;
    VAO(VAO&& other);
    VAO& operator=(VAO&& other);

    [[nodiscard]] constexpr size_t getVerticesCount() const {
        return m_numVertices;
    }
    [[nodiscard]] constexpr size_t getIndicesCount() const {
        return m_numIndices;
    }
    void setVertexBuffer() const;
    void setVertexSubBuffer(const std::vector<float>& vertices) const;
    void setElementBuffer() const;
    void bind() const;

   private:
    void calcVerticesCount();
    void release();
    VBO m_vbo;
    std::optional<EBO> m_ebo;
    size_t m_numVertices;
    size_t m_numIndices;
    GLuint m_id;
};
}  // namespace Graphics