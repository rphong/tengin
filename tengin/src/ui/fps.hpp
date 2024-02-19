#pragma once

#include "../graphics/textRenderer.hpp"

const float REFRESH_RATE = 0.5f;

class FPS {
   public:
    void draw(Graphics::TextRenderer& renderer, const float& deltaTime);

   private:
    float currFPS = 0.0f;
    float timer = 0.0f;
    uint32_t frameCount = 0;
};