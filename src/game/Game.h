#pragma once

#include <SDL.h>

constexpr int FPS{144};
constexpr int MILLISECS_PER_FRAME = 1000 / FPS;

class Game {
private:
    bool isRunning;
    uint32_t millisecsPreviousFrame{0};
    SDL_Window *window{};
    SDL_Renderer *renderer{};
public:
    Game();

    ~Game();

    void initialize();

    void run();

    void setup();

    void processInput();

    void update();

    void render();

    void destroy();

    int windowWidth{};
    int windowHeight{};
};
