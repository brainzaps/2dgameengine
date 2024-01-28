//
// Created by Konstantin Skrypak on 28.01.2024.
//

#include <iostream>
#include <SDL2/SDL.h>
#include "Game.h"

Game::Game() {
    // TODO(Skrypak): Implement
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

    SDL_Window *window = SDL_CreateWindow(
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

    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, 0);

    if (!renderer) {
        std::cerr << "Error creating SDL renderer" << std::endl;
        return;
    }

    std::cout << "Game initialized" << std::endl;
}

void Game::Run() {
    // TODO(Skrypak): Implement
    std::cout << "Game run" << std::endl;
}

void Game::ProcessInput() {
    // TODO(Skrypak): Implement
    std::cout << "Game process input" << std::endl;
}

void Game::Update() {
    // TODO(Skrypak): Implement
    std::cout << "Game update" << std::endl;
}

void Game::Render() {
    // TODO(Skrypak): Implement
    std::cout << "Game render" << std::endl;
}

void Game::Destroy() {
    // TODO(Skrypak): Implement
    std::cout << "Game destroy" << std::endl;
}