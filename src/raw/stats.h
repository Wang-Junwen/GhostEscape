#ifndef STATS_H
#define STATS_H

#include "../core/actor.h"

class Stats : public Object
{
protected:
    Actor *parent_ = nullptr; // 父节点
    float health_ = 100.0f;
    float max_health_ = 100.0f;
    float mana_ = 100.0f;
    float max_mana_ = 100.0f;
    float damage_ = 40.0f;
    float mana_regen_ = 10.0f;

    float invincible_timer_ = 0.0f;
    float invincible_time_ = 1.5f;
    bool is_alive_ = true;
    bool is_invincible_ = false;

public:
    static Stats *addStatsChild(Actor *parent, float max_health = 100.0f, float max_mana = 100.0f, float damage = 40.0f, float mana_regen = 10.0f);
    virtual void update(float dt) override;

    bool canUseMana(float mana_cost) const;
    void useMana(float mana_cost);
    void regenMana(float dt);
    void takeDamage(float damage);

    // getters and setters
    Actor *getParent() const { return parent_; }
    float getHealth() const { return health_; }
    float getMaxHealth() const { return max_health_; }
    float getMana() const { return mana_; }
    float getMaxMana() const { return max_mana_; }
    float getDamage() const { return damage_; }
    float getManaRegen() const { return mana_regen_; }
    bool getAlive() const { return is_alive_; }
    void setParent(Actor *parent) { parent_ = parent; }
    void setHealth(float health) { health_ = health; }
    void setMaxHealth(float max_health) { max_health_ = max_health; }
    void setMana(float mana) { mana_ = mana; }
    void setMaxMana(float max_mana) { max_mana_ = max_mana; }
    void setDamage(float damage) { damage_ = damage; }
    void setManaRegen(float mana_regen) { mana_regen_ = mana_regen; }
    void setAlive(bool is_alive) { is_alive_ = is_alive; }
    float getInvincibleTime() const { return invincible_time_; }
    void setInvincibleTime(float time) { invincible_time_ = time; }
    float getInvincibleTimer() const { return invincible_timer_; }
    void setInvincibleTimer(float timer) { invincible_timer_ = timer; }
    bool getInvincible() const { return is_invincible_; }
    void setInvincible(bool is_invincible) { is_invincible_ = is_invincible; }

    float getHealthPercent() const { return health_ / max_health_; }
    float getManaPercent() const { return mana_ / max_mana_; }
};

#endif // STATS_H