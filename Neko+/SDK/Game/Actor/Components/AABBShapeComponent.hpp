#pragma once
#include "../../../../Utils/Math.h"
#include "../../../../Utils/OffsetManager.h"
#include "../../../../Utils/SigManager.h"

struct AABBShapeComponent {
    glm::vec3 mMin;
    glm::vec3 mMax;
    float mWidth;
    float mHeight;
};

static_assert(sizeof(AABBShapeComponent) == 0x20);