#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include <glm.hpp>
#include "Game.h"
#include "../logger/Logger.h"
#include "../ECS/ECS.h"

Game::Game() {
    isRunning = false;

    Logger::log("Game constructor called.");
}

Game::~Game() {
    Logger::log("Game destructor called.");
};

void Game::initialize() {
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        Logger::log("Error initializing SDL.");
        return;
    }

    //    use SDL_DisplayMode for fake fullscreen
    //    SDL_DisplayMode displayMode;
    //    SDL_GetCurrentDisplayMode(0, &displayMode);
    windowWidth = 800; //displayMode.w; -> use these for fake fullscreen
    windowHeight = 600; //displayMode.h;
    window = SDL_CreateWindow(
            NULL,
            SDL_WINDOWPOS_CENTERED,
            SDL_WINDOWPOS_CENTERED,
            windowWidth,
            windowHeight,
            SDL_WINDOW_BORDERLESS
    );
    if (!window) {
        Logger::error("Error creating SDL window.");
        return;
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (!renderer) {
        Logger::error("Error creating SDL renderer.");
        return;
    }
    // use this for real fullscreen
//    SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN);

    isRunning = true;
}

void Game::run() {
    setup();
    while (isRunning) {
        processInput();
        update();
        render();
    }
};

void Game::setup() {
    // TODO:zrtujsrtusu
    // Entity tank

}

void Game::processInput() {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        switch (event.type) {
            case SDL_QUIT:
                isRunning = false;
                break;
            case SDL_KEYDOWN:
                if (event.key.keysym.sym == SDLK_ESCAPE) {
                    isRunning = false;
                    break;
                }
        }
    };
};


void Game::update() {
    // if we are too fast, waste some time until we reach the MILLISECS_PER_FRAME
    // UNCOMMENT TO CAP FPS
//    uint32_t timeToWait{MILLISECS_PER_FRAME - (SDL_GetTicks() - millisecsPreviousFrame)};
//    if (timeToWait > 0 && timeToWait <= MILLISECS_PER_FRAME) {
//        SDL_Delay(timeToWait);
//    }

    // difference in ticks since the last frame converted to seconds
    // delta time helps the game speed to be the same regardless of FPS
    double deltaTime{(SDL_GetTicks() - millisecsPreviousFrame) / 1000.0};
    // store the current frame time
    millisecsPreviousFrame = SDL_GetTicks();

};

void Game::render() {
    SDL_SetRenderDrawColor(renderer, 21, 21, 21, 255);
    SDL_RenderClear(renderer);



    SDL_RenderPresent(renderer);
};

void Game::destroy() {
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

