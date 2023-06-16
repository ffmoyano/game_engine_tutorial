//
// Created by ffmoy on 16/06/2023.
//

#pragma once

class MovementSystem: public System {
public:
    MovementSystem() {
        // TODO: RequireComponent<TransformComponent>();
    }
    void update() {
        for(auto entity: getEntities()) {
            // TODO: update entity position based on its velocity
        }
    }

};