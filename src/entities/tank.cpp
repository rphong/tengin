#include "tank.hpp"

Tank::Tank(const glm::vec2& pos, const float& angle, const float& speed) {
    m_pos = pos;
    m_tankAngle = angle;
    m_speed = speed;
}

[[nodiscard]] glm::vec2 Tank::getPosition() const {
    return m_pos;
}

[[nodiscard]] float Tank::getRotation() const {
    return m_tankAngle;
}

[[nodiscard]] float Tank::getSpeed() const {
    return m_speed;
}

void Tank::move(const float& dist) {
    float x = m_pos.x;
    float y = m_pos.y;
    x += cos(glm::radians(m_tankAngle)) * dist;
    y += sin(glm::radians(m_tankAngle)) * dist;

    m_pos.x = x;
    m_pos.y = y;
}

void Tank::rotate(const float& angle) {
    m_tankAngle += angle;

    if(m_tankAngle < 0.0f) {
        m_tankAngle += 360.0f;
    } else if(m_tankAngle > 360.0f) {
        m_tankAngle -= 360.0f;
    }
}