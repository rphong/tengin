#include "debug.hpp"

const std::vector<float> squareVert = {-0.01f, -0.01f, 0.0f,   -0.01f,
                                       0.01f,  0.0f,   0.01f,  0.01f,
                                       0.0f,   0.01f,  -0.01f, 0.0f};
const std::vector<int> squareAttribLen = {3};
const std::vector<GLuint> indices = {0, 1, 2, 2, 0, 3};

Debug::Debug()
    : m_vaoSquare(Graphics::VAO(
          Graphics::VBO(squareVert, squareAttribLen, GL_STATIC_DRAW),
          Graphics::EBO(indices))),
      m_shader(Graphics::Shader("../tengin/src/shaders/solidColor.vertex.glsl",
                                "../tengin/src/shaders/solidColor.frag.glsl")) {
  m_shader.use();
  const glm::mat4 projection =
      glm::ortho(-1.0f, 1.0f, -1.0f, 1.0f, 0.1f, 100.0f);

  const glm::mat4 view =
      glm::lookAt(glm::vec3(0.0f, 0.0f, 3.0f), glm::vec3(0.0f, 0.0f, 0.0f),
                  glm::vec3(0.0f, 1.0f, 0.0f));

  m_shader.setMat4("projection", projection);
  m_shader.setMat4("view", view);
}

void Debug::drawPoint(const glm::vec2& pt, const glm::vec4& color,
                      const float& size) const {
  m_vaoSquare.bind();
  m_shader.use();

  glm::mat4 model = glm::mat4(1.0f);
  model = glm::scale(model, glm::vec3(size, size, size));
  model = glm::translate(model, glm::vec3(pt, 0.0f));
  m_shader.setMat4("model", model);
  m_shader.setFloat4("color", color);
  glDrawElements(GL_TRIANGLES, m_vaoSquare.getIndicesCount(), GL_UNSIGNED_INT,
                 0);
}

void Debug::drawPoints(const std::vector<glm::vec2>& pts,
                       const glm::vec4& color, const float& size) const {
  m_vaoSquare.bind();
  m_shader.use();

  for (const glm::vec2& pt : pts) {
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(pt, 0.0f));
    model = glm::scale(model, glm::vec3(size, size, size));
    m_shader.setMat4("model", model);
    m_shader.setFloat4("color", color);
    glDrawElements(GL_TRIANGLES, m_vaoSquare.getIndicesCount(), GL_UNSIGNED_INT,
                   0);
  }
}
