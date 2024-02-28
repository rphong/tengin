#include "entity.hpp"

glm::vec2 Entity::colldies(const Entity& other) {
    const std::vector<glm::vec2> o_hitbox = other.getHitbox();

    const auto m_edges = m_hitbox 
        | std::views::slide(2) 
        | std::views::transform(
            [](const auto& pair) {
                return glm::normalize(pair[1] - pair[0]);
            });

    const auto o_edges = o_hitbox 
        | std::views::slide(2) 
        | std::views::transform(
            [](const auto& pair) {
                return glm::normalize(pair[1] - pair[0]); 
            });

    const auto m_axis = m_edges
        | std::views::transform(
            [](const auto& edge) {
                return glm::vec2{-edge.y, edge.x};
            });

    const auto o_axis = o_edges
        | std::views::transform(
            [](const auto& edge) {
                return glm::vec2{-edge.y, edge.x};
            });

    glm::vec2 mtvAxis;
    float mtvOverlap = INT_MAX;

    for(const auto& axis: m_axis) {
        Projection p1 = project(m_hitbox, axis);
        Projection p2 = project(o_hitbox, axis);

        const float overlap = p1.overlap(p2);
        if(overlap == 0) return {0, 0};
        else if(overlap < mtvOverlap) {
            mtvAxis = axis;
            mtvOverlap = overlap;
        }
    }

    for(const auto& axis: o_axis) {
        Projection p1 = project(m_hitbox, axis);
        Projection p2 = project(o_hitbox, axis);

        const float overlap = p1.overlap(p2);
        if(overlap == 0) return {0, 0};
        else if(overlap < mtvOverlap) {
            mtvAxis = axis;
            mtvOverlap = overlap;
        }
    }

    return mtvAxis * mtvOverlap;
}


