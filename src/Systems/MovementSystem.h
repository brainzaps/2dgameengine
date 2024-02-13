//
// Created by Konstantin Skrypak on 01.02.2024.
//

#pragma once

#include "../ECS/ECS.h"
#include "../Components/TransformComponent.h"
#include "../Components/RigidBodyComponent.h"
#include "../Logger/Logger.h"

class MovementSystem : public System {
public:
    MovementSystem() {
        RequireComponent<TransformComponent>();
        RequireComponent<RigidBodyComponent>();
    }

    void Update(double deltaTime) {
        for (Entity entity: GetEntities()) {
            auto &transform = entity.GetComponent<TransformComponent>();
            const auto rigidBody = entity.GetComponent<RigidBodyComponent>();

            transform.position += (rigidBody.velocity * static_cast<float>(deltaTime));

            Logger::Log("Entity moved to: " + std::to_string(transform.position.x) + ", " +
                        std::to_string(transform.position.y));
        }
    }
};
