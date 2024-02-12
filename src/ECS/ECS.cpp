//
// Created by Konstantin Skrypak on 01.02.2024.
//

#include <vector>

#include "ECS.h"
#include "../Logger/Logger.h"

int IComponent::nextId = 0;

int Entity::GetId() const {
    return id;
}

void System::AddEntity(Entity entity) {
    entities.push_back(entity);
}

void System::RemoveEntity(Entity entity) {
    entities.erase(std::remove_if(entities.begin(), entities.end(), [&entity](Entity other) {
        return entity == other;
    }), entities.end());
}

std::vector <Entity> System::GetEntities() const {
    return entities;
}

const Signature &System::GetSignature() const {
    return signature;
}

Entity Registry::CreateEntity() {
    int entityId = numEntities++;

    Entity entity(entityId);
    entity.registry = this;
    entitiesToBeAdded.insert(entity);

    if (entityId >= entityComponentSignatures.size()) {
        entityComponentSignatures.resize(entityId + 1);
    }

    Logger::Log("Entity created with id: " + std::to_string(entityId));

    return entity;
}

void Registry::Update() {
    for (auto entity: entitiesToBeAdded) {
        AddEntityToSystems(entity);
    }
    entitiesToBeAdded.clear();
}

void Registry::AddEntityToSystems(Entity entity) {
    const auto entityId = entity.GetId();

    const auto &entityComponentsSignature = entityComponentSignatures[entityId];

    for (auto &system: systems) {
        const auto &systemSignature = system.second->GetSignature();

        bool isInterested = (entityComponentsSignature & systemSignature) == systemSignature;

        if (isInterested) {
            system.second->AddEntity(entity);
        }
    }
}