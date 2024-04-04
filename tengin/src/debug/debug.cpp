#include "debug.hpp"

const std::vector<float> squareVert = {
  -0.01f, -0.01f, 0.0f,
  -0.01f,  0.01f, 0.0f, 
   0.01f,  0.01f, 0.0f,
   0.01f,  -0.01f, 0.0f
};
const std::vector<float> arrowVert = {
  -0.01f, -0.01f, 0.0f, 0.0f, 0.0f, 
  -0.01f,  0.01f, 0.0f, 0.0f, 1.0f,
   0.01f,  0.01f, 0.0f, 1.0f, 1.0f, 
   0.01f, -0.01f, 0.0f, 1.0f, 0.0f
};

const std::vector<int> squareAttribLen = {3};
const std::vector<int> arrowAttribLen = {3, 2};
const std::vector<GLuint> squareIndices = {0, 1, 2, 2, 0, 3};

Debug::Debug()
    : m_vaoSquare(Graphics::VAO(
          Graphics::VBO(squareVert, squareAttribLen, GL_STATIC_DRAW),
          Graphics::EBO(squareIndices))),
      m_vaoArrow(Graphics::VAO(
          Graphics::VBO(arrowVert, arrowAttribLen, GL_STATIC_DRAW),
          Graphics::EBO(squareIndices))),
      m_colorShader(
          Graphics::Shader("../tengin/src/shaders/solidColor.vertex.glsl",
                           "../tengin/src/shaders/solidColor.frag.glsl")),
      m_textureShader(
          Graphics::Shader("../tengin/src/shaders/texture.vertex.glsl",
                           "../tengin/src/shaders/texture.frag.glsl")),
      m_arrowTexture("../tengin/src/resources/textures/solid_arrow.png",
                     GL_RGBA) {
  const glm::mat4 projection =
      glm::ortho(-1.0f, 1.0f, -1.0f, 1.0f, 0.1f, 100.0f);

  const glm::mat4 view =
      glm::lookAt(glm::vec3(0.0f, 0.0f, 3.0f), glm::vec3(0.0f, 0.0f, 0.0f),
                  glm::vec3(0.0f, 1.0f, 0.0f));

  m_colorShader.use();
  m_colorShader.setMat4("projection", projection);
  m_colorShader.setMat4("view", view);

  m_textureShader.use();
  m_textureShader.setMat4("projection", projection);
  m_textureShader.setMat4("view", view);
  m_textureShader.setInt("texture1", 0);
}

void Debug::drawPoint(const glm::vec2& pt, const glm::vec4& color,
                      const float& size) const {
  m_vaoSquare.bind();
  m_colorShader.use();

  glm::mat4 model = glm::mat4(1.0f);
  model = glm::translate(model, glm::vec3(pt, 0.0f));
  model = glm::scale(model, glm::vec3(size, size, size));
  m_colorShader.setMat4("model", model);
  m_colorShader.setFloat4("color", color);
  glDrawElements(GL_TRIANGLES, m_vaoSquare.getIndicesCount(), GL_UNSIGNED_INT,
                 0);
}

void Debug::drawPoints(const std::vector<glm::vec2>& pts,
                       const glm::vec4& color, const float& size) const {
  m_vaoSquare.bind();
  m_colorShader.use();

  for (const glm::vec2& pt : pts) {
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(pt, 0.0f));
    model = glm::scale(model, glm::vec3(size, size, size));
    m_colorShader.setMat4("model", model);
    m_colorShader.setFloat4("color", color);
    glDrawElements(GL_TRIANGLES, m_vaoSquare.getIndicesCount(), GL_UNSIGNED_INT,
                   0);
  }
}

void Debug::drawArrow(const glm::vec2& pt, const glm::vec2& dir,
                      const float& size) const {
  m_vaoArrow.bind();
  m_textureShader.use();
  m_arrowTexture.draw(GL_TEXTURE0);
  float angle = atan2(dir.y, dir.x);

  glm::vec4 tint = {1.0f, 1.0f, 1.0f, 1.0f};
  glm::mat4 model = glm::mat4(1.0f);
  model = glm::translate(model, glm::vec3(pt, 0.0f));
  model = glm::scale(model, glm::vec3(5, 5, 5));
  model = glm::rotate(model, angle, glm::vec3(0.0f, 0.0f, 1.0f));
  m_textureShader.setMat4("model", model);
  m_textureShader.setFloat4("tint", tint);
  glDrawElements(GL_TRIANGLES, m_vaoArrow.getIndicesCount(), GL_UNSIGNED_INT,
                 0);
}