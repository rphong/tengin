#pragma once

#include <vector>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "../graphics/vao.hpp"
#include "../graphics/buffer.hpp"
#include "../graphics/shader.hpp"

class Debug {
   public:
    Debug();
    void drawPoint(const glm::vec2& pt, const glm::vec4& color,
                    const float& size) const;
    void drawPoints(const std::vector<glm::vec2>& pts, const glm::vec4& color,
                    const float& size) const;

   private:
    Graphics::VAO m_vaoSquare;
    Graphics::Shader m_shader;
};