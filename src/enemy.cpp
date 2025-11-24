#include "enemy.h"
#include "raw/stats.h"
#include "affiliate/affiliate_bar.h"

Enemy *Enemy::addEnemyChild(Object *parent, glm::vec2 pos, Player *target)
{
    auto enemy = new Enemy();
    enemy->init();
    enemy->setPosition(pos);
    enemy->setTarget(target);
    if (parent) parent->addChild(enemy);
    return enemy;
}

void Enemy::init()
{
    Actor::init();
    anim_idle_ = SpriteAnim::addSpriteAnimChild(this, "assets/sprite/knight/WALK-sheet.png", 1.6f);
    anim_hurt_ = SpriteAnim::addSpriteAnimChild(this, "assets/sprite/knight/HURT-sheet.png", 1.6f);
    anim_die_ = SpriteAnim::addSpriteAnimChild(this, "assets/sprite/knight/DEATH-sheet.png", 1.6f);
    anim_hurt_->setActive(false);
    anim_die_->setActive(false);
    anim_die_->setLoop(false);

    cur_anim_ = anim_idle_;
    collider_ = Collider::addColliderChild(this, anim_idle_->getSize() * 0.6f);
    stats_ = Stats::addStatsChild(this);
    auto size = anim_idle_->getSize();
    health_bar_ = AffiliateBar::addAffiliateBarChild(this, glm::vec2(size.x * 0.7, 8), Anchor::BOTTOM_CENTER);
    health_bar_->setOffset(health_bar_->getOffset() + glm::vec2(0, size.y/2.0f));
    setType(ObjectType::ENEMY);
}

void Enemy::update(float dt)
{
    Actor::update(dt);
    if (target_->getActive() && cur_state_ != EnemyState::DIE)
    {
        aimTarget(target_);
        move(dt);
        attack();
    }
    checkState();
    remove();
}

void Enemy::aimTarget(Player *player)
{
    if (player == nullptr)
        return;
    
    auto direction = player->getPosition() - this->getPosition();
    if (glm::length(direction) != 0.0f)
        direction = glm::normalize(direction);
    velocity_ = direction * max_speed_;
}

void Enemy::checkState()
{
    EnemyState new_state;
    if (stats_->getHealth() <= 0) new_state = EnemyState::DIE;
    else if (stats_->getInvincible()) new_state = EnemyState::HURT;
    else new_state = EnemyState::IDLE;

    if (new_state != cur_state_) changeState(new_state);
    cur_anim_->setFlip(velocity_.x < 0);

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
    if (!collider_ || !target_ || target_->getCollider() == nullptr)
        return;
    if (collider_->isColliding(*target_->getCollider()))
    {
        if (stats_ && target_->getStats())
        {
            target_->takeDamage(stats_->getDamage());
        }
    }
}

void Enemy::remove()
{
    if (anim_die_->getFinish())
    {
        this->setNeedRemove(true);
    }
}
