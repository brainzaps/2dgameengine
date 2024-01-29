//
// Created by Konstantin Skrypak on 28.01.2024.
//

#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <glm/glm.hpp>

#include "Game.h"
#include "Logger.h"

Game::Game() {
    isRunning = false;
    Logger::Log("Game constructor");
}

Game::~Game() {
    // TODO(Skrypak): Implement
    Logger::Log("Game destructor");
}

void Game::Initialize() {
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        Logger::Log("Error initializing SDL");
        return;
    }

    SDL_DisplayMode displayMode;
    SDL_GetCurrentDisplayMode(0, &displayMode);

    windowWidth = displayMode.w;
    windowHeight = displayMode.h;

    window = SDL_CreateWindow(
            NULL,
            SDL_WINDOWPOS_CENTERED,
            SDL_WINDOWPOS_CENTERED,
            windowWidth,
            windowHeight,
            SDL_WINDOW_BORDERLESS
    );

    if (!window) {
        Logger::Err("Error creating SDL window");
        return;
    }

    renderer = SDL_CreateRenderer(window, -1, 0);

    if (!renderer) {
        Logger::Err("Error creating SDL renderer");
        return;
    }

    SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN);

    isRunning = true;

    Logger::Log("Game is initialized");
}

glm::vec2 playerPosition;
glm::vec2 playerVelocity;

void Game::Setup() {
    playerPosition = glm::vec2(0.0f, 0.0f);
    playerVelocity = glm::vec2(100.0f, 0.0f);

    Logger::Log("Game setup");
}

void Game::Run() {
    Setup();

    while (isRunning) {
        ProcessInput();
        Update();
        Render();
    }
}

void Game::ProcessInput() {
    SDL_Event event;

    while (SDL_PollEvent(&event)) {
        switch (event.type) {
            case SDL_QUIT: {
                isRunning = false;
                break;
            }
            case SDL_KEYDOWN: {
                if (event.key.keysym.sym == SDLK_ESCAPE) {
                    isRunning = false;
                }
                break;
            }
        }
    }

    Logger::Log("Game process input");
}

void Game::Update() {

    int timeToWait = MILLIS_PER_FRAME - (SDL_GetTicks() - ticksLastFrame);

    if (timeToWait > 0 && timeToWait <= MILLIS_PER_FRAME) {
        SDL_Delay(timeToWait);
    }

    double deltaTime = (SDL_GetTicks() - ticksLastFrame) / 1000.0;

    ticksLastFrame = SDL_GetTicks();

    glm::vec2 distance = playerVelocity * static_cast<float>(deltaTime);
    playerPosition += distance;

    Logger::Log("Game update");
}

void Game::Render() {
    Logger::Log("Game render");

    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    SDL_RenderClear(renderer);

    // Load PNG image
    SDL_Surface *surface = IMG_Load("./assets/images/tank-tiger-right.png");
    SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);


    // Render image
    SDL_Rect sourceRectangle = {
            static_cast<int>(playerPosition.x),
            static_cast<int>(playerPosition.y),
            32,
            32
    };
    SDL_RenderCopy(renderer, texture, NULL, &sourceRectangle);
    SDL_DestroyTexture(texture);

    SDL_RenderPresent(renderer);
}

void Game::Destroy() {
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    Logger::Log("Game is destroyed");
}