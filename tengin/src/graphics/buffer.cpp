#include "buffer.hpp"

using Graphics::EBO;
using Graphics::VBO;

VBO::VBO(const std::vector<float>& vertices,
         const std::vector<int>& attributeLengths, const int& drawType)
    : m_numVertices(vertices.size()), m_attribLengths(attributeLengths) {
  glGenBuffers(1, &m_id);
  glBindBuffer(GL_ARRAY_BUFFER, m_id);
  glBufferData(GL_ARRAY_BUFFER, m_numVertices * sizeof(float), &vertices[0],
               drawType);
}

VBO::VBO(const int& size, const std::vector<int>& attributeLengths,
         const int& drawType)
    : m_attribLengths(attributeLengths) {
  glGenBuffers(1, &m_id);
  glBindBuffer(GL_ARRAY_BUFFER, m_id);
  glBufferData(GL_ARRAY_BUFFER, size * sizeof(float), NULL, drawType);
}

VBO::~VBO() { release(); }

VBO::VBO(VBO&& other)
    : m_numVertices(other.m_numVertices),
      m_id(other.m_id),
      m_attribLengths(other.m_attribLengths) {
  other.m_id = 0;
}

VBO& VBO::operator=(VBO&& other) {
  if (this != &other) {
    release();
    std::swap(m_id, other.m_id);
    std::swap(m_attribLengths, other.m_attribLengths);
    std::swap(m_numVertices, other.m_numVertices);
  }
  return *this;
}

void VBO::bind() const { glBindBuffer(GL_ARRAY_BUFFER, m_id); }

void VBO::release() {
  glDeleteBuffers(1, &m_id);
  m_id = 0;
}

EBO::EBO(const std::vector<GLuint>& indices) : m_numIndices(indices.size()) {
  glGenBuffers(1, &m_id);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_id);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLuint),
               &indices[0], GL_STATIC_DRAW);
}

EBO::~EBO() { release(); }

EBO::EBO(EBO&& other) : m_numIndices(other.m_numIndices), m_id(other.m_id) {
  other.m_id = 0;
}

EBO& EBO::operator=(EBO&& other) {
  if (this != &other) {
    release();
    std::swap(m_id, other.m_id);
    std::swap(m_numIndices, other.m_numIndices);
  }
  return *this;
}

void EBO::bind() const { glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_id); }

void EBO::release() {
  glDeleteBuffers(1, &m_id);
  m_id = 0;
}