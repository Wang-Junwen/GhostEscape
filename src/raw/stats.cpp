#include "stats.h"

Stats *Stats::addStatsChild(Actor *parent, float max_health, float max_mana, float damage, float mana_regen)
{
    Stats *stats = new Stats();
    stats->setParent(parent);
    stats->setMaxHealth(max_health);
    stats->setHealth(max_health);
    stats->setMaxMana(max_mana);
    stats->setMana(max_mana);
    stats->setDamage(damage);
    stats->setManaRegen(mana_regen);
    parent->addChild(stats);
    return stats;
}

void Stats::update(float dt)
{
    Object::update(dt);
    regenMana(dt);
    // 无敌计时
    if (is_invincible_){
        invincible_timer_ += dt;
        if (invincible_timer_ >= invincible_time_){
            is_invincible_ = false;
            invincible_timer_ = 0.0f;
        }
    }
}

bool Stats::canUseMana(float mana_cost) const
{
    return mana_ >= mana_cost;
}

void Stats::useMana(float mana_cost)
{
    mana_ -= mana_cost;
    if (mana_ < 0.0f)
        mana_ = 0.0f;
}

void Stats::regenMana(float dt)
{
    mana_ += mana_regen_ * dt;
    if (mana_ > max_mana_)
        mana_ = max_mana_;
}

void Stats::takeDamage(float damage)
{
    // if (is_invincible_ || !is_alive_)
    if (is_invincible_)
        return;
    health_ -= damage;
    if (health_ <= 0.0f)
    {
        health_ = 0.0f;
        is_alive_ = false;
    }
    is_invincible_ = true;
    invincible_timer_ = 0.0f;
    // SDL_Log("Actor took %.2f damage, current health: %.2f", damage, health_);
}
