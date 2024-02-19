//
// Created by Konstantin Skrypak on 01.02.2024.
//

#pragma once

#include <glm/glm.hpp>
#include <string>

struct SpriteComponent {
    int width;
    int height;
    std::string assetId;

    SpriteComponent(std::string assetId = "", int width = 0, int height = 0) {
        this->assetId = assetId;
        this->width = width;
        this->height = height;
    }
};


