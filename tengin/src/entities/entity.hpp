#pragma once

#include <glm/glm.hpp>

#include <vector>
#include <cmath>
#include <ranges>
#include <algorithm>

class Entity {
 public:
  constexpr Entity(const glm::vec2& pos, const unsigned int& collisionLevel)
      : m_pos(pos), m_collisionLevel(collisionLevel){};
  void constexpr nudge(glm::vec2 translation) {
    m_pos += translation;
    updateHitbox();
  }
  glm::vec2 colldies(const Entity& other) const;

 protected:
  void constexpr virtual updateHitbox() = 0;
  [[nodiscard]] constexpr unsigned int getCollisionLevel() const {
    return m_collisionLevel;
  }
  glm::vec2 m_pos;
  std::vector<glm::vec2> m_hitbox;

 private:
  struct Projection;

  [[nodiscard]] Projection project(const std::vector<glm::vec2>& hitbox,
                                   const glm::vec2& axis) const;
  const unsigned int m_collisionLevel;
};
