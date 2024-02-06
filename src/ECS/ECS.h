//
// Created by Konstantin Skrypak on 01.02.2024.
//

#pragma once

#include <bitset>
#include <vector>
#include <unordered_map>
#include <typeindex>
#include <set>

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

    bool operator==(const Entity &other) const {
        return id == other.id;
    }

    bool operator!=(const Entity &other) const {
        return id != other.id;
    }

    bool operator<(const Entity &other) const {
        return id < other.id;
    }

    bool operator>(const Entity &other) const {
        return id > other.id;
    }
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


class IPool {
public:
    virtual ~IPool() = default;
};

class Registry {
private:
    int numEntities = 0;
    std::vector<IPool *> componentPools;

    std::vectory <Signature> entityComponentSignatures;
    std::unordered_map<std::type_index, System *> systems;

    std::set <Entity> entitiesToBeAdded;
    std::set <Entity> entitiesToBeKilled;

public:
    Registry() = default;

    ~Registry() = default;

    Entity CreateEntity();

    void Update();

    void AddEntityToSystem(Entity entity);
};


template<typename T>
class Pool : public IPool {
private:
    std::vector <T> data;
public:
    Pool(int size = 100) {
        data.resize(size);
    }

    virtual   ~Pool() = default;

    bool isEmpty() const {
        return data.empty();
    }

    int GetSize() const {
        return data.size();
    }

    void Resize(int size) {
        data.resize(size);
    }

    void Clear() {
        data.clear();
    }

    void Ad(T object) {
        data.push_back(object);
    }

    void Set(int index, T object) {
        data[index] = object;
    }

    T &Get(unsigned int index) {
        return static_cast<T &>(data[index]);
    }

    T &operator[](unsigned int index) {
        return static_cast<T &>(data[index]);
    }
};

template<typename T>
void System::RequireComponent() {
    const auto componentId = Component<T>::GetId();
    signature.set(componentId);
}



