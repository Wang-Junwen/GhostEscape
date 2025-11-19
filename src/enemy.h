#ifndef ENEMY_H
#define ENEMY_H

#include "player.h"
#include "affiliate/sprite_anim.h"


class Enemy : public Actor
{
    enum class EnemyState
    {
        IDLE,
        HURT,
        DIE
    };
    EnemyState cur_state_ = EnemyState::IDLE;
    Player *target_ = nullptr;
    SpriteAnim *anim_idle_ = nullptr;
    SpriteAnim *anim_hurt_ = nullptr;
    SpriteAnim *anim_die_ = nullptr;

    SpriteAnim *cur_anim_ = nullptr;

public:
    static Enemy *addEnemyChild(Object *parent, glm::vec2 pos, Player *target);

    virtual void init() override;
    virtual void update(float dt) override;

    void aimTarget(Player *player);

    void checkState();
    void changeState(EnemyState state);
    void attack();
    void remove();

    // getters and setters
    Player *getTarget() const { return target_; }
    void setTarget(Player *target) { target_ = target; }
};

#endif // ENEMY_H