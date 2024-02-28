#pragma once

#include <glm/glm.hpp>

#include <vector>
#include <cmath>
#include <ranges>
#include <iostream>
#include <algorithm>

class Entity {
   public:
    constexpr Entity(const unsigned int& collisionLevel,
                     const std::vector<glm::vec2>& vert = {})
        : m_hitbox(vert), m_collisionLevel(collisionLevel){};
    bool colldies(const Entity& other);

    void constexpr setHitbox(const std::vector<glm::vec2>& hitbox) {
        m_hitbox = hitbox;
        m_hitbox.push_back(m_hitbox[0]);
    }
    [[nodiscard]] constexpr std::vector<glm::vec2> getHitbox() const {
        return m_hitbox;
    }
    [[nodiscard]] constexpr unsigned int getCollisionLevel() const {
        return m_collisionLevel;
    }

   private:
    struct Projection {
        Projection(std::ranges::min_max_result<float> minmax) {
            const auto [low, high] = minmax;
            min = low;
            max = high;
        }
        [[nodiscard]] constexpr bool overlap(const Projection& o) {
            return std::max(min, o.min) <= std::min(max, o.max);
        }

        float min;
        float max;
    };
    [[nodiscard]] Projection project(const std::vector<glm::vec2>& hitbox,
                                     const glm::vec2& axis) const {
        const auto dotProducts = hitbox 
            | std::views::transform([&axis](const auto& pt) {
                return std::abs(glm::dot(pt, axis));
            });
        return Projection(std::ranges::minmax(dotProducts));
    }

    std::vector<glm::vec2> m_hitbox;
    const unsigned int m_collisionLevel;
};