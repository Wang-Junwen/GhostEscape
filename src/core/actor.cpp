#include "actor.h"
#include "scene.h"
#include "../raw/stats.h"

void Actor::move(float dt)
{
    auto pos_ = glm::clamp(position_ + velocity_ * dt, glm::vec2(0.0f), game_.getCurrentScene()->getWorldSize()); // 边界检测
    setPosition(pos_);
}

void Actor::takeDamage(float damage)
{
    if (!stats_) return;
    stats_->takeDamage(damage);
    
}

bool Actor::getIsAlive() const
{
    if (!stats_) return true;
    return stats_->getAlive();
}

