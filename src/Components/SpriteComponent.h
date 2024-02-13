//
// Created by Konstantin Skrypak on 01.02.2024.
//

#pragma once

#include <glm/glm.hpp>

struct SpriteComponent {
    int width;
    int height;

    SpriteComponent(int width = 0, int height = 0) {
        this->width = width;
        this->height = height;
    }
};


