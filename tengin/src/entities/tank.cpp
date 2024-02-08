#include "tank.hpp"

const std::vector<float> vert = {
    -0.1f, -0.1f, 0.0f, 0.0f, 0.0f, 
    -0.1f,  0.1f, 0.0f, 0.0f, 1.0f,
     0.1f,  0.1f, 0.0f, 1.0f, 1.0f, 
     0.1f, -0.1f, 0.0f, 1.0f, 0.0f};
const std::vector<int> attribLen = {3, 2};
const std::vector<GLuint> indices = {0, 1, 2, 2, 0, 3};

Tank::Tank(const glm::vec2& pos, const float& angle, const float& speed)
    : m_pos(pos),
      m_tankAngle(angle),
      m_barrelAngle(angle),
      m_speed(speed),
      m_texture("../tengin/src/resources/textures/green_tank.png", GL_RGBA),
      m_vao(Graphics::VAO(Graphics::VBO(vert, attribLen, GL_STATIC_DRAW),
            Graphics::EBO(indices))) {}

void Tank::draw(const Graphics::Shader& shader) const {
    m_vao.bind();
    m_texture.draw(GL_TEXTURE0);

    glm::mat4 model = glm::mat4(1.0f);
    model = glm::scale(model, glm::vec3(0.5f, 0.5f, 0.5f));
    model = glm::translate(model, glm::vec3(m_pos, 0.0f));
    model = glm::rotate(model, glm::radians(m_tankAngle),
                        glm::vec3(0.0f, 0.0f, 1.0f));
    shader.setMat4("model", model);

    if (m_vao.getIndicesCount() != 0) {
        glDrawElements(GL_TRIANGLES, m_vao.getIndicesCount(), GL_UNSIGNED_INT,
                       0);
    } else {
        glDrawArrays(GL_TRIANGLES, 0, m_vao.getVerticesCount());
    }
}

[[nodiscard]] glm::vec2 Tank::getPosition() const { return m_pos; }