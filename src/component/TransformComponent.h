#pragma once

#include "vec2.hpp"

struct TransformComponent {
    glm::vec2 position;
    glm::vec2 scale;
    double rotation;
};
