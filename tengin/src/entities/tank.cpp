#include "tank.hpp"

Tank::Tank(Graphics::VAO&& vao, const glm::vec2& pos, const float& angle,
           const float& speed)
    : m_vao(std::move(vao)),
      m_pos(pos),
      m_tankAngle(angle),
      m_barrelAngle(angle),
      m_speed(speed) {}

void Tank::draw(const Graphics::Shader& shader) const {
    m_vao.bind();
    
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