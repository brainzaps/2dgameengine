//
// Created by Konstantin Skrypak on 28.01.2024.
//

#include <iostream>
#include <SDL2/SDL.h>
#include "Game.h"

Game::Game() {
    isRunning = false;
    std::cout << "Game constructor" << std::endl;
}

Game::~Game() {
    // TODO(Skrypak): Implement
    std::cout << "Game destructor" << std::endl;
}

void Game::Initialize() {
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        std::cerr << "Error initializing SDL" << std::endl;
        return;
    }

    window = SDL_CreateWindow(
            NULL,
            SDL_WINDOWPOS_CENTERED,
            SDL_WINDOWPOS_CENTERED,
            800,
            600,
            SDL_WINDOW_BORDERLESS
    );

    if (!window) {
        std::cerr << "Error creating SDL window" << std::endl;
        return;
    }

    renderer = SDL_CreateRenderer(window, -1, 0);

    if (!renderer) {
        std::cerr << "Error creating SDL renderer" << std::endl;
        return;
    }

    isRunning = true;

    std::cout << "Game is initialized" << std::endl;
}

void Game::Run() {
    std::cout << "Game is running" << std::endl;

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

    std::cout << "Game process input" << std::endl;
}

void Game::Update() {
    // TODO(Skrypak): Implement
    std::cout << "Game update" << std::endl;
}

void Game::Render() {
    std::cout << "Game render" << std::endl;

    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    SDL_RenderClear(renderer);

    SDL_RenderPresent(renderer);
}

void Game::Destroy() {
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    std::cout << "Game is destroyed" << std::endl;
}