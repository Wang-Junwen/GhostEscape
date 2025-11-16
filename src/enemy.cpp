#include "enemy.h"

void Enemy::init()
{
    Actor::init();
    anim_idle_ = SpriteAnim::addSpriteAnimChild(this, "assets/sprite/ghost-Sheet.png", 2.0f);
    anim_hurt_ = SpriteAnim::addSpriteAnimChild(this, "assets/sprite/ghostHurt-Sheet.png", 2.0f);
    anim_die_ = SpriteAnim::addSpriteAnimChild(this, "assets/sprite/ghostDead-Sheet.png", 2.0f);
    anim_hurt_->setActive(false);
    anim_die_->setActive(false);
    anim_die_->setLoop(false);

    cur_anim_ = anim_idle_;
    collider_ = Collider::addColliderChild(this, anim_idle_->getSize());
}

void Enemy::update(float dt)
{
    Actor::update(dt);
    aimTarget(target_);
    move(dt);
    
    attack();
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

void Enemy::checkState()
{
}

void Enemy::changeState(EnemyState state)
{
    if (state == cur_state_)
        return;
    cur_anim_->setActive(false);
    switch (state)
    {
    case EnemyState::IDLE:
        cur_anim_ = anim_idle_;

        break;
    case EnemyState::HURT:
        cur_anim_ = anim_hurt_;
        break;
    case EnemyState::DIE:
        cur_anim_ = anim_die_;
        break;
    }
    cur_anim_->setActive(true);
    cur_state_ = state;
}

void Enemy::attack()
{
    if (!collider_ || target_->getCollider() == nullptr)
        return;
    if (collider_->isColliding(*target_->getCollider())){
        // TODO: 造成伤害
        SDL_Log("attack");
    }
}

void Enemy::remove()
{
    if (anim_die_->getFinish())
    {
        this->setNeedRemove(true);
    }
}
