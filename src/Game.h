//
// Created by Konstantin Skrypak on 28.01.2024.
//

#pragma once

#include <SDL2/SDL.h>

class Game {
private:
    bool isRunning;
    SDL_Window *window;
    SDL_Renderer *renderer;
public:
    Game();

    ~Game();

    int windowWidth;
    int windowHeight;

    void Initialize();

    void Setup();

    void Run();

    void ProcessInput();

    void Update();

    void Render();

    void Destroy();
};

