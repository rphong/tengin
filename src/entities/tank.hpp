#pragma once

#include <glm/glm.hpp>

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

class Tank {
   public:
    Tank(const glm::vec2& pos, const float& angle = 0.0f, const float& speed = 0.1f);
    [[nodiscard]] glm::vec2 getPosition() const;
    [[nodiscard]] float getRotation() const;
    [[nodiscard]] float getSpeed() const;
    void move(const float& dist);
    void rotate(const float& angle);

   private:
    glm::vec2 m_pos;
    float m_tankAngle;
    float m_barrelAngle;
    float m_speed;
};