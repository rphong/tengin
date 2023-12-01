#include "vao.hpp"

VAO::VAO(VBO&& vbo) : m_vbo(std::move(vbo)), m_numIndices(0) {
    calcVerticesCount();
    
    glGenVertexArrays(1, &m_id);
    setVertexBuffer();
}

VAO::VAO(VBO&& vbo, EBO&& ebo)
    : m_vbo(std::move(vbo)),
      m_numIndices(ebo.getNumIndices()),
      m_ebo(std::move(ebo)) {
    calcVerticesCount();

    glGenVertexArrays(1, &m_id);
    setVertexBuffer();
    setElementBuffer();
}

VAO::~VAO() { glDeleteVertexArrays(1, &m_id); }

VAO::VAO(VAO&& other)
    : m_id(other.m_id),
      m_vbo(std::move(other.m_vbo)),
      m_ebo(std::move(other.m_ebo)),
      m_numVertices(other.m_numVertices),
      m_numIndices(other.m_numIndices) {
    other.m_id = 0;
}

VAO& VAO::operator=(VAO&& other) {
    if (this != &other) {
        release();
        std::swap(m_id, other.m_id);
        std::swap(m_vbo, other.m_vbo);
        std::swap(m_ebo, other.m_ebo);
        std::swap(m_numVertices, other.m_numVertices);
        std::swap(m_numIndices, other.m_numIndices);
    }
    return *this;
}

void VAO::setVertexBuffer() const {
    bind();
    m_vbo.bind();

    const std::vector<int>& attributes = m_vbo.getAttribVec();
    const unsigned int& stride =
        std::accumulate(attributes.begin(), attributes.end(), 0);
    int offset = 0;

    for (int i = 0; i < attributes.size(); ++i) {
        glVertexAttribPointer(i, attributes[i], GL_FLOAT, GL_FALSE,
                              stride * sizeof(float),
                              (void*)(offset * sizeof(float)));
        glEnableVertexAttribArray(i);
        offset += attributes[i];
    }
}

void VAO::setElementBuffer() const {
    bind();
    m_ebo->bind();
}

void VAO::bind() const { glBindVertexArray(m_id); }

void VAO::calcVerticesCount() {
    const std::vector<int>& attributes = m_vbo.getAttribVec();
    const unsigned int& stride =
        std::accumulate(attributes.begin(), attributes.end(), 0);
    m_numVertices = m_vbo.getNumVertices() / stride;
}

void VAO::release() {
    glDeleteVertexArrays(1, &m_id);
    m_id = 0;
}