#pragma once

#include <glad/glad.h>

#include <vector>

namespace Graphics {
class VBO {
   public:
    VBO(const std::vector<float>& vertices,
        const std::vector<int>& attributeLengths, const int& drawType);
    VBO(const int& size, const std::vector<int>& attributeLenghts,
        const int& drawType);
    ~VBO();
    VBO(const VBO&) = delete;
    VBO& operator=(const VBO&) = delete;
    VBO(VBO&& other);
    VBO& operator=(VBO&& other);

    void bind() const;
    [[nodiscard]] constexpr size_t getNumVertices() const {
        return m_numVertices;
    }
    [[nodiscard]] constexpr std::vector<int> getAttribVec() const {
        return m_attribLengths;
    }

   private:
    size_t m_numVertices;
    GLuint m_id;
    std::vector<int> m_attribLengths;
    void release();
};

class EBO {
   public:
    EBO(const std::vector<GLuint>& indices);
    ~EBO();
    EBO(const EBO&) = delete;
    EBO& operator=(const EBO&) = delete;
    EBO(EBO&& other);
    EBO& operator=(EBO&& other);

    void bind() const;
    [[nodiscard]] constexpr size_t getNumIndices() const {
        return m_numIndices;
    }

   private:
    size_t m_numIndices;
    GLuint m_id;
    void release();
};
}  // namespace Graphics
