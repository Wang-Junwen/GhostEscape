#ifndef ACTOR_H
#define ACTOR_H

#include "object_world.h"

class Actor : public ObjectWorld
{
protected:
    glm::vec2 velocity_ = glm::vec2(0.0f); // 速度
    float max_speed_ = 100.0f;               // 最大速度

public:
    void move(float dt);
    // getters and setters
    glm::vec2 getVelocity() const { return velocity_; }
    void setVelocity(const glm::vec2 &vel) { velocity_ = vel; }
    float getMaxSpeed() const { return max_speed_; }
    void setMaxSpeed(float max_speed) { max_speed_ = max_speed; }
};

#endif // ACTOR_H