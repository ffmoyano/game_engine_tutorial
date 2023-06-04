#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include <glm.hpp>
#include "Game.h"

Game::Game() {
    isRunning = false;
    std::cout << "Game constructor called" << std::endl;
}

Game::~Game() {
    std::cout << "Game destructor called\n";
};

void Game::initialize() {
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        std::cerr << "Error initializing SDL.\n";
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
        std::cerr << "Error creating SDL window.\n";
        return;
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (!renderer) {
        std::cerr << "Error creating SDL renderer.\n";
        return;
    }
    // use this for real fullscreen
    SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN);

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

glm::vec2 playerPosition;
glm::vec2 playerVelocity;

void Game::setup() {
    playerPosition = glm::vec2(10.0, 20.0);
    playerVelocity = glm::vec2(1.0, 0.0);
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
    uint32_t timeToWait {MILLISECS_PER_FRAME - (SDL_GetTicks() - millisecsPreviousFrame)};
    if (timeToWait > 0 && timeToWait <= MILLISECS_PER_FRAME) {
        SDL_Delay(timeToWait);
    }

    // store the current frame time
    millisecsPreviousFrame = SDL_GetTicks();

    playerPosition.x += playerVelocity.x;
    playerPosition.y += playerVelocity.y;
};

void Game::render() {
    SDL_SetRenderDrawColor(renderer, 21, 21, 21, 255);
    SDL_RenderClear(renderer);

    SDL_Surface *surface = IMG_Load("../assets/images/tank-tiger-right.png");
    SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);

    SDL_Rect dstRect{
            static_cast<int>(playerPosition.x),
            static_cast<int>(playerPosition.y),
            32,
            32
    }; // tank is 32x32 pixels

// if we want to pass the full image as our srcRect we can pass NULL
    SDL_RenderCopy(renderer, texture, NULL, &dstRect);

    SDL_DestroyTexture(texture);

    SDL_RenderPresent(renderer);
};

void Game::destroy() {
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

