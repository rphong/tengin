#define STB_IMAGE_IMPLEMENTATION

#include <glad/glad.h>
#include <glfw/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>
#include <array>
#include <vector>
#include <utility>
#include <cassert>

#include "entities/tank.hpp"
#include "graphics/textRenderer.hpp"
#include "graphics/texture.hpp"

constexpr glm::vec2 screenSize(1200, 800);

void processInput(GLFWwindow* window, Tank& player1, const float& delta);

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, height, width);
}

int main() {
    assert(glfwInit());
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window =
        glfwCreateWindow(screenSize.x, screenSize.y, "LearnOpenGL", NULL, NULL);
    assert(window);

    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    assert(gladLoadGLLoader((GLADloadproc)glfwGetProcAddress));

    Graphics::Shader shader("../tengin/src/shaders/entity.vertex.glsl",
                            "../tengin/src/shaders/entity.frag.glsl");

    Graphics::TextRenderer text(screenSize);

    const std::vector<float> bgVert{
        -0.8f, -0.8f, 0.0f, 0.0f, 0.0f, -0.8f, 0.8f,  0.0f, 0.0f, 1.0f,
        0.8f,  0.8f,  0.0f, 1.0f, 1.0f, 0.8f,  -0.8f, 0.0f, 1.0f, 0.0f};
    const std::vector<int> bgAttribLen{3, 2};
    const std::vector<GLuint> indices{0, 1, 2, 2, 0, 3};

    Graphics::VAO vaoFloor(Graphics::VBO(bgVert, bgAttribLen, GL_STATIC_DRAW),
                           Graphics::EBO(indices));

    Graphics::Texture texFloor(
        "../tengin/src/resources/textures/sand_floor.jpg", GL_RGB);

    shader.setInt("texture1", 0);
    shader.use();

    // Camera
    const glm::mat4 projection =
        glm::ortho(-1.0f, 1.0f, -1.0f, 1.0f, 0.1f, 100.0f);

    const glm::mat4 view =
        glm::lookAt(glm::vec3(0.0f, 0.0f, 3.0f), glm::vec3(0.0f, 0.0f, 0.0f),
                    glm::vec3(0.0f, 1.0f, 0.0f));

    shader.setMat4("projection", projection);
    shader.setMat4("view", view);

    Tank player1(glm::vec2(0.0f, 0.0f));
    float deltaTime = 0.0f, lastFrame = 0.0f;
    float FPSDisplayRate = 0.0f;
    float totalFrames = 0.0f;
    float FPS = 0.0f;

    while (!glfwWindowShouldClose(window)) {
        float currentFrame = static_cast<float>(glfwGetTime());
        ++totalFrames;
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;
        FPSDisplayRate += deltaTime;

        // Input
        processInput(window, player1, deltaTime);

        // Rendering commands
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        shader.use();

        // Enable transparency
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

        // Draw floor
        texFloor.draw(GL_TEXTURE0);

        vaoFloor.bind();
        glm::mat4 model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(0.0f));
        shader.setMat4("model", model);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        // Draw tank
        player1.draw(shader);

        // FPS
        text.RenderText(std::to_string(FPS), 25.0f, 25.0f, 1.0f,
                        glm::vec3(0.5, 0.8f, 0.2f));
        if (FPSDisplayRate >= 0.25) {
            FPS = totalFrames/currentFrame;
            FPSDisplayRate = 0;
        }
        // Check and call events & swap buffers
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    glfwTerminate();

    return 0;
}

void processInput(GLFWwindow* window, Tank& player1, const float& delta) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    // Movement
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        player1.move(player1.getSpeed() * delta);
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        player1.move(-player1.getSpeed() * delta);
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) player1.rotate(0.05f);
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) player1.rotate(-0.05f);
}