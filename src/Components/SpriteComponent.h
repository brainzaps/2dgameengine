//
// Created by Konstantin Skrypak on 01.02.2024.
//

#pragma once

#include <SDL2/SDL.h>
#include <glm/glm.hpp>
#include <string>

struct SpriteComponent {
    int width;
    int height;
    std::string assetId;
    SDL_Rect srcRect;

    SpriteComponent(std::string assetId = "", int width = 0, int height = 0, int srcRectX = 0, int srcRectY = 0) {
        this->assetId = assetId;
        this->width = width;
        this->height = height;
        this->srcRect = {srcRectX, srcRectY, width, height};
    }
};


