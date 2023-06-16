#pragma once

#include <iostream>
#include <bitset>
#include <vector>

const unsigned int MAX_COMPONENTS = 32;

// Siganture: we use a bitset (1s and 0s)
// to keep track of which components an entity has
// and also helps keep track of which entites a system is interested in.
typedef std::bitset<MAX_COMPONENTS> Signature;

struct Component {
    int id;
};

class Entity {
private:
    int id;
public:
    Entity(int id) : id(id) {};

    int getId() const;
};

class System {
private:
    // which components an entity must have for the system to consider the entity
    Signature componentSignature;
    // List of all entites that the system is interested in
    std::vector<Entity> entities;
public:
    System() = default;

    ~System() = default;

    void addEntity(Entity entity);

    void RemoveEntity(Entity entity);

    std::vector<Entity> getEntities() const;

    Signature &getComponentSignature() const;
};

class Registry {

};