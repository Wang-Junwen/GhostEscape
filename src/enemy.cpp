#include "enemy.h"
#include "affiliate/sprite_anim.h"

void Enemy::init()
{
    Actor::init();
    SpriteAnim::addSpriteAnimChild(this, "assets/sprite/ghost-Sheet.png", 2.0f);
}

void Enemy::update(float dt)
{
    Actor::update(dt);
    aimTarget(target_);
    move(dt);
}

void Enemy::aimTarget(Player *player)
{
    if (target_ == nullptr)
        return;
    auto direction = player->getPosition() - this->getPosition();
    if (glm::length(direction) != 0.0f)
        direction = glm::normalize(direction);
    velocity_ = direction * max_speed_;
}
