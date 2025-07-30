#pragma once

struct ActorRotationComponent {
public:
    float mPitch;
    float mYaw;
    float mOldPitch;
    float mOldYaw;
};

static_assert(sizeof(ActorRotationComponent) == 0x10);