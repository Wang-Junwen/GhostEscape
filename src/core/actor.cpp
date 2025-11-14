#include "actor.h"
#include "scene.h"

void Actor::move(float dt)
{
    auto pos_ = glm::clamp(position_ + velocity_ * dt, glm::vec2(0.0f), game_.getCurrentScene()->getWorldSize()); // 边界检测
    setPosition(pos_);
}
