#pragma once

#include <glm/glm.hpp>

#include <vector>
#include <cmath>
#include <ranges>
#include <iostream>
#include <algorithm>

class Entity {
   public:
    constexpr Entity(const glm::vec2& pos,
                     const unsigned int& collisionLevel)
        : m_pos(pos), m_collisionLevel(collisionLevel){};
    void constexpr nudge(glm::vec2 translation) {
        m_pos += translation;
        updateHitbox();
    }
    glm::vec2 colldies(const Entity& other);

   protected:
    void constexpr virtual updateHitbox() = 0;
    [[nodiscard]] constexpr std::vector<glm::vec2> getHitbox() const {
        return m_hitbox;
    }
    [[nodiscard]] constexpr unsigned int getCollisionLevel() const {
        return m_collisionLevel;
    }

    glm::vec2 m_pos;
    std::vector<glm::vec2> m_hitbox;

   private:
    struct Projection {
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

    [[nodiscard]] Projection project(const std::vector<glm::vec2>& hitbox,
                                     const glm::vec2& axis) const {
        const auto dotProducts =
            hitbox | std::views::transform([&axis](const auto& pt) {
                return glm::dot(pt, axis);
            });
        return Projection(std::ranges::minmax(dotProducts));
    }

    const unsigned int m_collisionLevel;
};
