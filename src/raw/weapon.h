#ifndef WEAPON_H
#define WEAPON_H

#include "../core/object.h"

class Spell;
class Actor;
class Weapon : public Object
{
protected:
    Actor *parent_ = nullptr;
    float cool_down_ = 1.0f;
    float mana_cost_ = 10.0f;
    float cool_down_timer_ = 0.0f;

public:
    
    virtual void update(float dt) override;

    bool canAttack();
    void attack(glm::vec2 position, Spell *spell);

    // getters and setters
    Actor *getParent() const { return parent_; }
    void setParent(Actor *value) { parent_ = value; }
    float getCoolDown() const { return cool_down_; }
    void setCoolDown(float value) { cool_down_ = value; }
    float getManaCost() const { return mana_cost_; }
    void setManaCost(float value) { mana_cost_ = value; }
    float getCoolDownTimer() const { return cool_down_timer_; }
    void setCoolDownTimer(float value) { cool_down_timer_ = value; }
};

#endif // WEAPON_H