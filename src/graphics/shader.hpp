#pragma once

#include <glad/glad.h>
#include <glm/glm.hpp>

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

class Shader {
   public:
    unsigned int m_ID;

    Shader(const std::string& vertexPath, const std::string fragmentPath);
    void use();
    void setBool(const std::string& name, const bool& value) const;
    void setInt(const std::string& name, const int& value) const;
    void setFloat(const std::string& name, const float& value) const;
    void setMat4(const std::string& name, const glm::mat4& model) const;

   private:
    void printError(const std::string& stage, const GLenum& pname, const unsigned int& shader = 0) const;
};