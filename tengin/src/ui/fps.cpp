#include "fps.hpp"

void FPS::draw(Graphics::TextRenderer& renderer, const float& deltaTime) {
  if (timer >= REFRESH_RATE) {
    currFPS = frameCount / timer;
    frameCount = 0;
    timer = 0;
  } else {
    frameCount++;
    timer += deltaTime;
  }
  renderer.RenderText(std::to_string(currFPS), 25.0f, 25.0f, 0.5f,
                      glm::vec3(0.5, 0.8f, 0.2f));
}