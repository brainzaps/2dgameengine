//
// Created by Konstantin Skrypak on 28.01.2024.
//

#pragma once

#include <SDL2/SDL.h>
#include <memory>

#include "../ECS/ECS.h"
#include "../AssetStore/AssetStore.h"

const int FPS = 60;
const int MILLISECS_PER_FRAME = 1000 / FPS;

class Game {
private:
    bool isRunning;
    bool isDebug;
    int millisecsPreviousFrame = 0;
    SDL_Window *window;
    SDL_Renderer *renderer;

    std::unique_ptr <Registry> registry;
    std::unique_ptr <AssetStore> assetStore;

public:
    Game();

    ~Game();

    void Initialize();

    void Run();

    void Setup();

    void LoadLevel(int level);

    void ProcessInput();

    void Update();

    void Render();

    void Destroy();

    int windowWidth;
    int windowHeight;
};

