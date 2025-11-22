#ifndef ACTOR_H
#define ACTOR_H

#include "object_world.h"

class AffiliateBar;
class Stats;
class Actor : public ObjectWorld
{
protected:
    glm::vec2 velocity_ = glm::vec2(0.0f); // 速度
    float max_speed_ = 100.0f;             // 最大速度

    Stats *stats_ = nullptr;             // 状态
    AffiliateBar *health_bar_ = nullptr; // 生命条

public:
    virtual void update(float dt) override;

    void move(float dt);
    virtual void takeDamage(float damage);

    // getters and setters
    glm::vec2 getVelocity() const { return velocity_; }
    void setVelocity(const glm::vec2 &vel) { velocity_ = vel; }
    float getMaxSpeed() const { return max_speed_; }
    void setMaxSpeed(float max_speed) { max_speed_ = max_speed; }
    Stats *getStats() const { return stats_; }
    void setStats(Stats *stats) { stats_ = stats; }
    bool getIsAlive() const;
    AffiliateBar *getHealthBar() const { return health_bar_; }
    void setHealthBar(AffiliateBar *health_bar) { health_bar_ = health_bar; }
private:
    void updateHealthBar();
};

#endif // ACTOR_H