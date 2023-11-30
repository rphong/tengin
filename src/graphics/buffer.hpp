#pragma once

#include <glad/glad.h>

#include <vector>

class VBO {
   public:
    VBO(const std::vector<float>& vertices, const std::vector<int>& attributeLengths);
    ~VBO();
    VBO(const VBO&) = delete;
    VBO& operator=(const VBO&) = delete;
    VBO(VBO&& other);
    VBO& operator=(VBO&& other);

    void bind() const;
    [[nodiscard]] constexpr std::vector<int> getAttribVec() const { return m_attribLengths; }

   private:
    void release();
    GLuint m_id;
    std::vector<int> m_attribLengths;
};

class EBO {
   public:
    EBO(const std::vector<GLuint>& indicies);
    ~EBO();
    EBO(const EBO&) = delete;
    EBO& operator=(const EBO&) = delete;
    EBO(EBO&& other);
    EBO& operator=(EBO&& other);

    void bind() const;

   private:
    void release();
    GLuint m_id;
};