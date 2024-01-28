//
// Created by Konstantin Skrypak on 28.01.2024.
//

#pragma once

#include <SDL2/SDL.h>

const int FPS = 60;
const int MILLIS_PER_FRAME = 1000 / FPS;

class Game {
private:
    bool isRunning;
    int ticksLastFrame = 0;
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

