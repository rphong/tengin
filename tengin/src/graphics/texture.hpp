#pragma once

#include <glad/glad.h>
#include <stb/stb_image.h>

#include <string>
#include <cassert>

namespace Graphics {
class Texture {
 public:
  Texture(const std::string& texPath, const GLenum& format);
  void draw(const GLenum& texture) const;

 private:
  void setWrap(const GLenum& s = GL_REPEAT, const GLenum& t = GL_REPEAT) const;
  void setFilter(const GLenum& min = GL_LINEAR,
                 const GLenum& mag = GL_LINEAR) const;
  GLuint m_id;
};
}  // namespace Graphics