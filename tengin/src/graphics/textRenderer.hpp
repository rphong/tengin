#pragma once

#include "./vao.hpp"
#include "./shader.hpp"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <map>
#include <string>

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

    bool validInitialLoad();
    void loadCharacters();
    void setTextureOptions() const;
    const glm::vec2 m_screenSize;
    Graphics::Shader m_shader;
    FT_Library m_ft;
    FT_Face m_face;
    VAO m_VAO;
    std::map<GLchar, Character> m_characters;
};
}  // namespace Graphics