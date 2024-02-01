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

struct IComponent {
protected:
    static int nextId;
};

template<typename T>
class Component : public IComponent {
    static int GetId() {
        static auto id = nextId++;
        return id;
    }
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

    const Signature &GetSignature() const;

    template<typename T>
    void RequireComponent();
};

class Registry {
};

template<typename T>
void System::RequireComponent() {
    const auto componentId = Component<T>::GetId();
    signature.set(componentId);
}



