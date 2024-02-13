//
// Created by Konstantin Skrypak on 01.02.2024.
//

#pragma once

#include <SDL2/SDL.h>

#include "../ECS/ECS.h"
#include "../Components/TransformComponent.h"
#include "../Components/SpriteComponent.h"
#include "../Logger/Logger.h"

class RenderSystem : public System {
public:
    RenderSystem() {
        RequireComponent<TransformComponent>();
        RequireComponent<SpriteComponent>();
    }

    void Update(SDL_Renderer *renderer) {
        for (Entity entity: GetEntities()) {
            auto transform = entity.GetComponent<TransformComponent>();
            const auto sprite = entity.GetComponent<SpriteComponent>();


            SDL_Rect objRect = {
                    static_cast<int>(transform.position.x),
                    static_cast<int>(transform.position.y),
                    sprite.width,
                    sprite.height
            };

            SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
            SDL_RenderFillRect(renderer, &objRect);
        }
    }
};
