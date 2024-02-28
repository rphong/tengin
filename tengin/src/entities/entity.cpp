#include "entity.hpp"

bool Entity::colldies(const Entity& other) {
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

    for(const auto& axis: m_axis) {
        Projection p1 = project(m_hitbox, axis);
        Projection p2 = project(o_hitbox, axis);
        if(!p1.overlap(p2)) return false;
    }

    for(const auto& axis: o_axis) {
        Projection p1 = project(m_hitbox, axis);
        Projection p2 = project(o_hitbox, axis);
        if(!p1.overlap(p2)) return false;
    }

    return true;
}


