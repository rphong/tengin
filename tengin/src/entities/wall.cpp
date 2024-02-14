#include "wall.hpp"

const std::vector<float> vert{
    -0.1f, -0.1f, 0.0f, 0.0f, 0.0f, 
    -0.1f,  0.1f, 0.0f, 0.0f, 1.0f,  
     0.1f,  0.1f, 0.0f, 1.0f, 1.0f,
     0.1f, -0.1f, 0.0f, 1.0f, 0.0f
};
const std::vector<int> attribLen = {3, 2};
const std::vector<GLuint> indices = {0, 1, 2, 2, 0, 3};

Wall::Wall(const glm::vec2& pos)
    : m_pos(pos),
      m_texture("../tengin/src/resources/textures/brick_wall.png", GL_RGB),
      m_vao(Graphics::VAO(Graphics::VBO(vert, attribLen, GL_STATIC_DRAW),
                          Graphics::EBO(indices))) {}