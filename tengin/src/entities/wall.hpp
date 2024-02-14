#pragma once

#include <glm/glm.hpp>

#include "../graphics/vao.hpp"
#include "../graphics/buffer.hpp"
#include "../graphics/shader.hpp"
#include "../graphics/texture.hpp"

class Wall {
   public:
    Wall(const glm::vec2& pos);
    void draw(const Graphics::Shader& shader) const;

   private:
    Graphics::VAO m_vao;
    Graphics::Texture m_texture;
    glm::vec2 m_pos;
};