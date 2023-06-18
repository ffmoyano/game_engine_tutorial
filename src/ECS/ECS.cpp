#include "ECS.h"

int Entity::getId() const {
    return id;
}

template<typename T>
void System::RequireComponent() {
    constexpr auto componentId = Component<T>::getId();
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


