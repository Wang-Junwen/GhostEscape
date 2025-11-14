#ifndef ENEMY_H
#define ENEMY_H

#include "player.h"

class Enemy : public Actor
{
    Player *target_ = nullptr;

public:
    virtual void init() override;
    virtual void update(float dt) override;

    void aimTarget(Player *player);

    // getters and setters
    Player *getTarget() const { return target_; }
    void setTarget(Player *target) { target_ = target; }
};

#endif // ENEMY_H