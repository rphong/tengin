#pragma once

#include <glad/glad.h>
#include <glm/glm.hpp>

#include <string>

namespace Graphics {
class Shader {
   public:
    Shader(const std::string& vertexPath, const std::string fragmentPath);
    ~Shader();
    void use() const;
    void setBool(const std::string& name, const bool& value) const;
    void setInt(const std::string& name, const int& value) const;
    void setFloat(const std::string& name, const float& value) const;
    void setFloat3(const std::string& name, const glm::vec3& values) const;
    void setFloat4(const std::string& name, const glm::vec4& values) const;
    void setMat4(const std::string& name, const glm::mat4& model) const;

   private:
    unsigned int m_ID;
    void printError(const std::string& stage, const GLenum& pname,
                    const unsigned int& shader = 0) const;
};
}  // namespace Graphics