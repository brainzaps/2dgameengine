//
// Created by Konstantin Skrypak on 28.01.2024.
//

#pragma once

class Game {
public:
    Game();

    ~Game();

    void Initialize();

    void Run();

    void ProcessInput();

    void Update();

    void Render();

    void Destroy();
};

