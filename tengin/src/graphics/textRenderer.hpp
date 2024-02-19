#pragma once

#include "./vao.hpp"
#include "./shader.hpp"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <map>
#include <string>
#include <cassert>

#include <ft2build.h>
#include FT_FREETYPE_H

namespace Graphics {

class TextRenderer {
    struct Character {
        // https://freetype.org/freetype2/docs/glyphs/glyph-metrics-3.svg
        unsigned int textureID;
        glm::ivec2 size;
        glm::ivec2 bearing;
        unsigned int advance;
    };

   public:
    TextRenderer(const glm::vec2& screenSize);
    void RenderText(const std::string& text, float x, const float& y,
                    const float& scale, const glm::vec3& color);

   private:
    constexpr static unsigned int FONTSIZE = 48;

    void loadCharacters();
    void setTextureOptions() const;
    Graphics::Shader m_shader;
    VAO m_VAO;
    std::map<GLchar, Character> m_characters;
    const glm::vec2 m_screenSize;
};
}  // namespace Graphics