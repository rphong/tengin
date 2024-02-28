#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "./entity.hpp"
#include "../graphics/vao.hpp"
#include "../graphics/buffer.hpp"
#include "../graphics/shader.hpp"
#include "../graphics/texture.hpp"

class Tank : public Entity {
   public:
    Tank(const glm::vec2& pos, const float& angle = 0.0f,
         const float& speed = 0.2f);
    void draw(const Graphics::Shader& shader) const;
    void constexpr move(const float& dist) {
        m_pos.x = m_pos.x + cos(glm::radians(m_tankAngle)) * dist;
        m_pos.y = m_pos.y + sin(glm::radians(m_tankAngle)) * dist;
        updateHitbox();
    }
    void constexpr rotate(const float& angle) {
        m_tankAngle += angle;

        if (m_tankAngle < 0.0f) {
            m_tankAngle += 360.0f;
        } else if (m_tankAngle > 360.0f) {
            m_tankAngle -= 360.0f;
        }
    }
    void constexpr updateHitbox() {
        setHitbox({rotatePoint({-0.05, -0.05}), rotatePoint({0.05, -0.05}),
                   rotatePoint({0.05, 0.05}), rotatePoint({-0.05, 0.05})});
    }

    [[nodiscard]] constexpr glm::vec2 getPosition() const { return m_pos; }
    [[nodiscard]] constexpr float getRotation() const { return m_tankAngle; }
    [[nodiscard]] constexpr float getSpeed() const { return m_speed; }

   private:
    [[nodiscard]] constexpr glm::vec2 rotatePoint(const glm::vec2& pt) {
        return {
            m_pos.x + (pt.x * cos(glm::radians(m_tankAngle)) -
                       pt.y * sin(glm::radians(m_tankAngle))),
            m_pos.y + (pt.x * sin(glm::radians(m_tankAngle)) +
                       pt.y * cos(glm::radians(m_tankAngle))),
        };
    }

    Graphics::VAO m_vao;
    Graphics::Texture m_texture;
    glm::vec2 m_pos;
    float m_tankAngle;
    float m_barrelAngle;
    float m_speed;
};