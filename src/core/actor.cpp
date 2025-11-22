#include "actor.h"
#include "scene.h"
#include "../raw/stats.h"
#include "../affiliate/affiliate_bar.h"

void Actor::update(float dt)
{
    ObjectWorld::update(dt);
    updateHealthBar();
}

void Actor::move(float dt)
{
    auto pos_ = glm::clamp(position_ + velocity_ * dt, glm::vec2(0.0f), game_.getCurrentScene()->getWorldSize()); // 边界检测
    setPosition(pos_);
}

void Actor::takeDamage(float damage)
{
    if (!stats_)
        return;
    stats_->takeDamage(damage);
}

bool Actor::getIsAlive() const
{
    if (!stats_)
        return true;
    return stats_->getAlive();
}

void Actor::updateHealthBar()
{
    if (!stats_ || !health_bar_)
        return;
    health_bar_->setPercentage(stats_->getHealth() / stats_->getMaxHealth());
}
