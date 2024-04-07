#include "entity.hpp"

struct Entity::Projection {
  Projection(std::ranges::min_max_result<float> minmax) {
    const auto [low, high] = minmax;
    min = low;
    max = high;
  }
  [[nodiscard]] constexpr float overlap(const Projection& o) {
    const float lower = std::max(min, o.min);
    const float upper = std::min(max, o.max);

    return lower <= upper ? upper - lower : 0;
  }

  float min;
  float max;
};

glm::vec2 Entity::colldies(const Entity& other) const {
  const std::vector<glm::vec2> o_hitbox = other.m_hitbox;

  const auto m_edges = m_hitbox | std::views::slide(2) |
                       std::views::transform([](const auto& pair) {
                         return glm::normalize(pair[1] - pair[0]);
                       });

  const auto o_edges = o_hitbox | std::views::slide(2) |
                       std::views::transform([](const auto& pair) {
                         return glm::normalize(pair[1] - pair[0]);
                       });

  const auto m_axis = m_edges | std::views::transform([](const auto& edge) {
                        return glm::vec2{-edge.y, edge.x};
                      });

  const auto o_axis = o_edges | std::views::transform([](const auto& edge) {
                        return glm::vec2{-edge.y, edge.x};
                      });

  glm::vec2 mtvAxis;
  float mtvOverlap = INT_MAX;

  for (const auto& axis : m_axis) {
    Projection p1 = project(m_hitbox, axis);
    Projection p2 = project(o_hitbox, axis);

    const float overlap = p1.overlap(p2);
    if (overlap == 0)
      return {0, 0};
    else if (overlap < mtvOverlap) {
      mtvAxis = axis;
      mtvOverlap = overlap;
    }
  }

  for (const auto& axis : o_axis) {
    Projection p1 = project(m_hitbox, axis);
    Projection p2 = project(o_hitbox, axis);

    const float overlap = p1.overlap(p2);
    if (overlap == 0)
      return {0, 0};
    else if (overlap < mtvOverlap) {
      mtvAxis = axis;
      mtvOverlap = overlap;
    }
  }

  if (glm::distance(m_pos + (mtvAxis * mtvOverlap), other.m_pos) <
      glm::distance(m_pos, other.m_pos)) {
    mtvAxis = -mtvAxis;
  }

  return mtvAxis * mtvOverlap;
}

Entity::Projection Entity::project(const std::vector<glm::vec2>& hitbox,
                                   const glm::vec2& axis) const {
  const auto dotProducts =
      hitbox | std::views::transform(
                   [&axis](const auto& pt) { return glm::dot(pt, axis); });
  return Projection(std::ranges::minmax(dotProducts));
}