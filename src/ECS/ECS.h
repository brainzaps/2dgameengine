//
// Created by Konstantin Skrypak on 01.02.2024.
//

#pragma once

#include <bitset>
#include <vector>

const unsigned int MAX_COMPONENTS = 32;

// We use bitset to keep track of which components an entity has,
// and also helps keep track of which entities a system is interested in.
typedef std::bitset <MAX_COMPONENTS> Signature;

class Component {
private:
    int id;
public:
    Component(int id) : id(id) {}

    int GetId() const;
};

class Entity {
private:
    int id;
public:
    Entity(int id) : id(id) {}

    int GetId() const;
};

class System {
private:
    Signature signature;
    std::vector <Entity> entities;
public:
    System() = default;

    ~System() = default;

    void AddEntity(Entity entity);

    void RemoveEntity(Entity entity);

    std::vector <Entity> GetEntities() const;

    Signature &GetSignature() const;
};

class Registry {
};