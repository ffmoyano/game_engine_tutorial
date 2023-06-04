#ifndef GAME_ENGINE_TUTORIAL_H
#define GAME_ENGINE_TUTORIAL_H

#include <SDL.h>

class Game {
private:
    bool isRunning;
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

    int windowWidth;
    int windowHeight;
};


#endif
