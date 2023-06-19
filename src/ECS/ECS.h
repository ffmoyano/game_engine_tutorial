#pragma once

#include <iostream>
#include <bitset>
#include <vector>
#include <typeindex>
#include <unordered_map>
#include <set>

const unsigned int MAX_COMPONENTS = 32;

// Signature: we use a bitset (1s and 0s)
// to keep track of which components an entity has
// and also helps keep track of which entites a system is interested in.
typedef std::bitset<MAX_COMPONENTS> Signature;

struct BaseComponent {
protected:
    static int nextId;
};

template<typename T>
class Component : public BaseComponent {
    static int getId() {
        static auto id = nextId++;
        return id;
    }
};

class Entity {
private:
    int id;
public:
    explicit Entity(int id) : id(id) {};

    Entity(const Entity &entity) = default;

    [[nodiscard]] int getId() const;

    // OPERATOR OVERLOADING
    Entity &operator=(const Entity &other) = default;

    bool operator==(const Entity &other) const { return id == other.id; }

    bool operator!=(const Entity &other) const { return id != other.id; }

    bool operator>(const Entity &other) const { return id > other.id; }

    bool operator<(const Entity &other) const { return id < other.id; }

};

class System {
private:
    // which components an entity must have for the system to consider the entity
    Signature componentSignature;
    // List of all entites that the system is interested in
    std::vector<Entity> entities;
public:
    System() = default;

    virtual ~System() = default;

    void addEntity(Entity entity);

    void RemoveEntity(Entity entity);

    [[nodiscard]] std::vector<Entity> getEntities() const;

    [[nodiscard]] const Signature &getComponentSignature() const;

    template<typename T>
    void RequireComponent();
};

class IPool {
public:
    virtual ~IPool() = default;
};

// pool is just a vector of generic objects
template<typename T>
class Pool : public IPool {
private:
    std::vector<T> data;
public:
    explicit Pool(int size = 100) {
        data.resize(size);
    }

    virtual ~Pool() = default;

    [[nodiscard]] bool isEmpty() const {
        return data.empty();
    }

    [[nodiscard]] int getSize() const {
        return data.size();
    }

    void resize(int n) {
        data.resize(n);
    }

    void clear() {
        data.clear();
    }

    void add(auto object) {
        data.push_back(object);
    }

    void set(int index, auto object) {
        data[index] = object;
    }

    auto &get(int index) {
        return data[index];
    }

    auto &operator[](unsigned int index) {
        return data[index];
    }
};


class Registry {
private:
    // keep track of how many entities were added to the scene
    int numEntities = 0;

    std::set<Entity> entitiesToAdd; // entities awaiting creation in the next registry update();
    std::set<Entity> entitiesToRemove; // entities awaiting destruction in the next registry update();

    // Vector of component pools
    // each pool contains all the data for a certain component type
    // [vector index = componentId], [pool index = entityId]
    std::vector<IPool *> componentPools;

    // Vector of component signatures
    // the signature lets us know thich components are turned "on" for an entity
    // [vector index = entityId]
    std::vector<Signature> entityComponentSignatures;

    // Map of active systems [index = system typeId]
    std::unordered_map<std::type_index, System *> systems;


public:
    Registry() = default;

    Entity createEntity();

    void killEntity(Entity entity);

    template<typename T, typename ...TArgs>
    void addComponent(Entity entity, TArgs &&...args);

    template<typename T>
    void removeComponent(Entity entity);

    template<typename T>
    bool hasComponent(Entity entity) const;

    template<typename T>
    T &getComponent(Entity entity) const;
};