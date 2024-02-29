//
// Created by Konstantin Skrypak on 01.02.2024.
//

#pragma once

#include <SDL2/SDL.h>

#include "../ECS/ECS.h"
#include "../Components/SpriteComponent.h"
#include "../Components/AnimationComponent.h"
#include "../Logger/Logger.h"

class AnimationSystem : public System {
public:
    AnimationSystem() {
        RequireComponent<SpriteComponent>();
        RequireComponent<AnimationComponent>();
    }

    void Update() {
        for (auto entity: GetEntities()) {
            auto &animation = entity.GetComponent<AnimationComponent>();
            auto &sprite = entity.GetComponent<SpriteComponent>();

            animation.currentFrame =
                    ((SDL_GetTicks() - animation.startTime) * animation.frameSpeedRate / 1000) % animation.numFrames;

            sprite.srcRect.x = sprite.width * animation.currentFrame;
        }

    }
};
