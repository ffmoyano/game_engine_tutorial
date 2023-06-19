#include "ECS.h"
#include "../logger/Logger.h"

int Entity::getId() const {
    return id;
}

template<typename T>
void System::RequireComponent() {
    const auto componentId = Component<T>::getId();
    componentSignature.set(componentId);
}

void System::addEntity(Entity entity) {
    entities.push_back(entity);
}

void System::RemoveEntity(Entity entityToRemove) {
//    entities.erase(
//            std::remove_if(
//                    entities.begin(), entities.end(),
//                    // lambda function with capture []
//                    [&entityToRemove](Entity entity) {
//                        return entityToRemove.getId() == entity.getId();
//                    }), entities.end());

    std::erase_if(entities, [&entityToRemove](Entity entity) {
        // we don't need to compare ids because operator overloading in entity class declaration
        return entityToRemove == entity;
    });
}

std::vector<Entity> System::getEntities() const {
    return entities;
}

const Signature &System::getComponentSignature() const {
    return componentSignature;
}

Entity Registry::createEntity() {
    int entityId = ++numEntities;
//    if (entityId >= entityComponentSignatures.size()) {
//        entityComponentSignatures.resize(++entityId);
//    }
    Logger::log("Entity created with id = " + std::to_string(entityId));
    Entity entity(entityId);
    entitiesToAdd.insert(entity);
    return entity;
}

template <typename T, typename ...TArgs>
void Registry::addComponent(Entity entity, TArgs &&...args) {
    const auto componentId = Component<T>::getId();
    const auto entityId = entity.getId();
    // if the component id is greater than the current size of the componentPools, then resize the vector
    if(componentId >= componentPools.size()) {
        componentPools.resize(componentId +1, nullptr);
    }

    // if we still dont't have a pool for that component type
    if(!componentPools(componentId)){
        auto* newPool = new Pool<T>();
        componentPools[componentId] = newPool;
    }

    // get the pool of component values for that component type
    auto* componentPool = Pool<T>(componentPools[componentId]);

    // if the entity id is greater than the current size of the component pool, then resize the pool
    if(entityId >= componentPool->getSize()) {
        componentPool->resize(numEntities);
    }

    // Create a new component object of type T and forward the various parameters to the constructor
    T newComponent(std::forward<TArgs>(args)...);

    // add the new component to the component pool list, using the entity id as index
    componentPool->set(entityId, newComponent);

    // change the component signature of the entity and set the component id on the bitset to 1
    entityComponentSignatures[entityId].set(componentId);
 }
