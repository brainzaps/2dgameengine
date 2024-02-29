//
// Created by Konstantin Skrypak on 26.02.2024.
//

#pragma once


#include <SDL2/SDL.h>

struct AnimationComponent {
    int numFrames;
    int currentFrame;
    int frameSpeedRate;
    bool isLoop;
    int startTime;

    AnimationComponent(int numFrames = 1, int frameSpeedRate = 1, bool isLoop = true) {
        this->numFrames = numFrames;
        this->frameSpeedRate = frameSpeedRate;
        this->isLoop = isLoop;
        this->currentFrame = 1;
        this->startTime = SDL_GetTicks();
    }
};
