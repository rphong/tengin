#include "texture.hpp"

using Graphics::Texture;

Texture::Texture(const std::string& texPath, const GLenum& format) {
    glGenTextures(1, &m_id);
    glBindTexture(GL_TEXTURE_2D, m_id);

    setWrap(GL_REPEAT);
    setFilter(GL_LINEAR);

    int width, height, nrChannels;
    unsigned char* data =
        stbi_load(texPath.c_str(), &width, &height, &nrChannels, 0);
    assert(data);

    glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format,
                 GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);

    stbi_image_free(data);
}

void Texture::draw(const GLenum& texture) const {
    glActiveTexture(texture);
    glBindTexture(GL_TEXTURE_2D, m_id);
}

void Texture::setWrap(const GLenum& s, const GLenum& t) const {
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, s);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, t);
}

void Texture::setFilter(const GLenum& min, const GLenum& mag) const {
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, min);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, mag);
}