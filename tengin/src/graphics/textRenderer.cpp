#include "textRenderer.hpp"

#include <vector>
#include <iostream>

using Graphics::TextRenderer;

TextRenderer::TextRenderer(const glm::vec2& screenSize)
    : m_screenSize(screenSize),
      m_VAO(Graphics::VBO(24, std::vector<int>{4}, GL_DYNAMIC_DRAW)),
      m_shader("../tengin/src/shaders/textRenderer.vertex.glsl",
               "../tengin/src/shaders/textRenderer.frag.glsl") {
    if (!validInitialLoad()) return;
    m_shader.use();
    m_shader.setMat4("projection",
                     glm::ortho(0.0f, static_cast<float>(screenSize.x), 0.0f,
                                static_cast<float>(screenSize.y)));

    FT_Set_Pixel_Sizes(m_face, 0, FONTSIZE);
    loadCharacters();

    FT_Done_Face(m_face);
    FT_Done_FreeType(m_ft);
}

void TextRenderer::loadCharacters() {
    // Disable byte-alignment restriction
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

    for (unsigned char c = 0; c < 128; ++c) {
        if (FT_Load_Char(m_face, c, FT_LOAD_RENDER)) {
            std::cout << "ERROR::FREETYTPE: Failed to load Glyph" << std::endl;
            continue;
        }
        unsigned int texture;
        glGenTextures(1, &texture);
        glBindTexture(GL_TEXTURE_2D, texture);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, m_face->glyph->bitmap.width,
                     m_face->glyph->bitmap.rows, 0, GL_RED, GL_UNSIGNED_BYTE,
                     m_face->glyph->bitmap.buffer);
        setTextureOptions();

        Character character = {
            texture,
            glm::ivec2(m_face->glyph->bitmap.width, m_face->glyph->bitmap.rows),
            glm::ivec2(m_face->glyph->bitmap_left, m_face->glyph->bitmap_top),
            static_cast<unsigned int>(m_face->glyph->advance.x)};
        m_characters.insert(std::pair<char, Character>(c, character));
    }
    glBindTexture(GL_TEXTURE_2D, 0);
}

void TextRenderer::RenderText(const std::string& text, float x, const float& y,
                              const float& scale, const glm::vec3& color) {
    m_shader.use();
    m_shader.setFloat3("textColor", color);
    glDisable(GL_DEPTH_TEST);   
    glActiveTexture(GL_TEXTURE0);
    m_VAO.bind();

    for (const auto& c : text) {
        const Character ch = m_characters[c];

        const float xpos = x + ch.bearing.x * scale;
        const float ypos = y - (ch.size.y - ch.bearing.y) * scale;

        const float w = ch.size.x * scale;
        const float h = ch.size.y * scale;
        const std::vector<float> vertices{
            xpos,     ypos + h, 0.0f, 0.0f, 
            xpos,     ypos,     0.0f, 1.0f,
            xpos + w, ypos,     1.0f, 1.0f, 
            xpos,     ypos + h, 0.0f, 0.0f,
            xpos + w, ypos,     1.0f, 1.0f, 
            xpos + w, ypos + h, 1.0f, 0.0f};
        // Render glyph texture over quad
        glBindTexture(GL_TEXTURE_2D, ch.textureID);
        m_VAO.setVertexSubBuffer(vertices);

        glBindBuffer(GL_ARRAY_BUFFER, 0);
        // Render quad
        glDrawArrays(GL_TRIANGLES, 0, 6);
        // Advance cursor(1/64th pixels)
        x += (ch.advance >> 6) * scale;
    }
    glBindVertexArray(0);
    glBindTexture(GL_TEXTURE_2D, 0);
}

void TextRenderer::setTextureOptions() const {
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
}

bool TextRenderer::validInitialLoad() {
    if (FT_Init_FreeType(&m_ft)) {
        std::cout << "ERROR::FREETYPE: Could not init FreeType Library"
                  << std::endl;
        return false;
    }
    if (FT_New_Face(m_ft, "../tengin/src/resources/fonts/Roboto-Medium.ttf", 0,
                    &m_face)) {
        std::cout << "ERROR::FREETYPE: Failed to load font" << std::endl;
        return false;
    }
    return true;
}