#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "./entity.hpp"
#include "../graphics/vao.hpp"
#include "../graphics/buffer.hpp"
#include "../graphics/shader.hpp"
#include "../graphics/texture.hpp"

class Wall : public Entity {
   public:
    Wall(const glm::vec2& pos);
    void draw(const Graphics::Shader& shader, const glm::vec4& tint) const;

   private:
    void constexpr updateHitbox() {
        m_hitbox = {{m_pos.x - 0.05, m_pos.y - 0.05},
                    {m_pos.x + 0.05, m_pos.y - 0.05},
                    {m_pos.x + 0.05, m_pos.y + 0.05},
                    {m_pos.x - 0.05, m_pos.y + 0.05}};
    }

    Graphics::VAO m_vao;
    Graphics::Texture m_texture;
};