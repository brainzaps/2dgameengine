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

    std::vector <Signature> entityComponentSignatures;
    std::unordered_map<std::type_index, System *> systems;

    std::set <Entity> entitiesToBeAdded;
    std::set <Entity> entitiesToBeKilled;

public:
    Registry() = default;

    ~Registry() = default;

    Entity CreateEntity();

    void Update();

    // Components management

    template<typename T, typename ...TArgs>
    void AddComponent(Entity entity, TArgs &&...args);

    template<typename T>
    void RemoveComponent(Entity entity);

    template<typename T>
    bool HasComponent(Entity entity) const;

    // Systems management

    template<typename T, typename ...TArgs>
    void AddSystem(TArgs &&...args);

    template<typename T>
    void RemoveSystem();

    template<typename T>
    T &GetSystem() const;

    template<typename T>
    bool HasSystem() const;


    void AddEntityToSystems(Entity entity);
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

    void Add(T object) {
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

template<typename T, typename ...TArgs>
void Registry::AddComponent(Entity entity, TArgs &&...args) {
    const int componentId = Component<T>::GetId();
    const int entityId = entity.GetId();


    if (componentPools.size() <= componentId) {
        componentPools.resize(componentId + 1, nullptr);
    }

    if (componentPools[componentId] == nullptr) {
        Pool<T> *pool = new Pool<T>();
        componentPools[componentId] = pool;
    }

    Pool<T> *pool = componentPools[componentId];

    if (entityId >= pool->GetSize()) {
        pool->Resize(entityId + 1);
    }

    T newComponent(std::forward<TArgs>(args)...);

    pool->Set(entityId, newComponent);

    entityComponentSignatures[entityId].set(componentId);
}

template<typename T>
void Registry::RemoveComponent(Entity entity) {
    const int componentId = Component<T>::GetId();
    const int entityId = entity.GetId();

    entityComponentSignatures[entityId].set(componentId, false);
}

template<typename T>
bool Registry::HasComponent(Entity entity) const {
    const int componentId = Component<T>::GetId();
    const int entityId = entity.GetId();

    return entityComponentSignatures[entityId].test(componentId);
}

template<typename T, typename ...TArgs>
void Registry::AddSystem(TArgs &&...args) {
    T *system = new T(std::forward<TArgs>(args)...);
    systems.insert(std::make_pair(std::type_index(typeid(T)), system));
}

template<typename T>
void Registry::RemoveSystem() {
    auto system = systems.find(std::type_index(typeid(T)));
    systems.erase(system);
}

template<typename T>
T &Registry::GetSystem() const {
    auto system = systems.find(std::type_index(typeid(T)));
    return *static_cast<T *>(system->second);
}

template<typename T>
bool Registry::HasSystem() const {
    return systems.find(std::type_index(typeid(T))) != systems.end();
}