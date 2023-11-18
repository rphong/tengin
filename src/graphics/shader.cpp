#include "shader.hpp"

Shader::Shader(const std::string& vertexPath, const std::string fragmentPath) {
    // Get vertex/fragment source code from files
    std::string vertexCode, fragmentCode;
    std::ifstream vShaderFile, fShaderFile;
    // Set exception mask for ifstreams
    vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    try {
        // Open file buffer content to streams
        vShaderFile.open(vertexPath);
        fShaderFile.open(fragmentPath);
        std::stringstream vShaderStream, fShaderStream;
        vShaderStream << vShaderFile.rdbuf();
        fShaderStream << fShaderFile.rdbuf();
        vShaderFile.close();
        fShaderFile.close();

        vertexCode = vShaderStream.str();
        fragmentCode = fShaderStream.str();
    } catch (std::ifstream::failure& e) {
        std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << std::endl;
    }
    const char* vShaderCode = vertexCode.c_str();
    const char* fShaderCode = fragmentCode.c_str();

    // Compile shaders
    int success;
    char infoLog[512];

    const unsigned int vertex = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex, 1, &vShaderCode, NULL);
    glCompileShader(vertex);
    glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
    if (!success) {
        printError("VERTEX", GL_COMPILE_STATUS, vertex);
    }

    const unsigned int fragment = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment, 1, &fShaderCode, NULL);
    glCompileShader(fragment);
    glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
    if (!success) {
        printError("FRAGMENT", GL_COMPILE_STATUS, fragment);
    }

    // Link to programs
    m_ID = glCreateProgram();
    glAttachShader(m_ID, vertex);
    glAttachShader(m_ID, fragment);
    glLinkProgram(m_ID);
    glGetProgramiv(m_ID, GL_LINK_STATUS, &success);
    if (!success) {
        std::cout << "hello linking failed" << std::endl;
        printError("PROGRAM", GL_LINK_STATUS);
    }

    glDeleteShader(vertex);
    glDeleteShader(fragment);
};

void Shader::use() {
    glUseProgram(m_ID);
}

void Shader::setBool(const std::string& name, const bool& value) const {
    glUniform1i(glGetUniformLocation(m_ID, name.c_str()), (int)value);
}

void Shader::setInt(const std::string& name, const int& value) const {
    glUniform1i(glGetUniformLocation(m_ID, name.c_str()), value);
}

void Shader::setFloat(const std::string& name, const float& value) const {
    glUniform1f(glGetUniformLocation(m_ID, name.c_str()), value);
}

void Shader::setMat4(const std::string& name, const glm::mat4& model) const {
    glUniformMatrix4fv(glGetUniformLocation(m_ID, name.c_str()), 1, GL_FALSE, &model[0][0]);
}

void Shader::printError(const std::string& stage, const GLenum& pname, const unsigned int& shader) const {
    char infoLog[512];
    std::string errorMessage = "ERROR::SHADER::" + stage + "::";

    if(pname == GL_COMPILE_STATUS) {
        glGetShaderInfoLog(shader, 512, NULL, infoLog);
        std::cout << errorMessage + "COMPILATION_FAILED\n" << infoLog << std::endl;
    } else if(pname == GL_LINK_STATUS) {
        glGetProgramInfoLog(m_ID, 512, NULL, infoLog);
        std::cout << errorMessage + "LINKING_FAILED\n" << infoLog << std::endl;
    }
}