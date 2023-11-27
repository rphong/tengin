#pragma once

#include <glm/glm.hpp>

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

class Tank {
   public:
    constexpr Tank(const glm::vec2& pos, const float& angle = 0.0f, const float& speed = 0.1f) 
        : m_pos(pos), m_tankAngle(angle), m_barrelAngle(angle), m_speed(speed) {}
    void constexpr move(const float& dist) {
        m_pos.x = m_pos.x + cos(glm::radians(m_tankAngle)) * dist;
        m_pos.y = m_pos.y + sin(glm::radians(m_tankAngle)) * dist;
    }
    void constexpr rotate(const float& angle) {
        m_tankAngle += angle;

        if (m_tankAngle < 0.0f) {
            m_tankAngle += 360.0f;
        } else if (m_tankAngle > 360.0f) {
            m_tankAngle -= 360.0f;
        }
    }
    [[nodiscard]] glm::vec2 getPosition() const;
    [[nodiscard]] constexpr float getRotation() const { return m_tankAngle; }
    [[nodiscard]] constexpr float getSpeed() const { return m_speed; }

   private:
    glm::vec2 m_pos;
    float m_tankAngle;
    float m_barrelAngle;
    float m_speed;
};