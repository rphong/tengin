#include "vao.hpp"

VAO::VAO(VBO&& vbo, EBO&& ebo)
    :m_vbo(std::move(vbo)), m_ebo(std::move(ebo)) {
    glGenVertexArrays(1, &m_id);
    setVertexBuffer();
    setElementBuffer();
}

VAO::~VAO() {
    glDeleteVertexArrays(1, &m_id);
}

VAO::VAO(VAO&& other)
    : m_id(other.m_id), m_vbo(std::move(other.m_vbo)), m_ebo(std::move(other.m_ebo)) {
    other.m_id = 0;
}

VAO& VAO::operator=(VAO&& other) {
    if (this != &other) {
        release();
        std::swap(m_id, other.m_id);
    }
    return *this;
}

void VAO::setVertexBuffer() {
    bind();
    m_vbo.bind();

    const std::vector<int>& attributes = m_vbo.getAttribVec();
    const int& stride = std::accumulate(attributes.begin(), attributes.end(), 0);
    int offset = 0;

    for (int i = 0; i < attributes.size(); ++i) {
        glVertexAttribPointer(i, attributes[i], GL_FLOAT, GL_FALSE, stride * sizeof(float), (void*)(offset * sizeof(float)));
        glEnableVertexAttribArray(i);
        offset += attributes[i];
    }
}

void VAO::setElementBuffer() {
    bind();
    m_ebo.bind();
}

void VAO::bind() const {
    glBindVertexArray(m_id);
}

void VAO::release() {
    glDeleteVertexArrays(1, &m_id);
    m_id = 0;
}