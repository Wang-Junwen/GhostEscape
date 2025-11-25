#ifndef PLAYER_H
#define PLAYER_H

#include "core/actor.h"
#include "affiliate/sprite_anim.h"
#include "world/effect.h"
#include "weapon_thunder.h"

class Player : public Actor
{
    enum PlayerState {
        IDLE,
        MOVE,
        HURT
    };

    PlayerState cur_state_ = IDLE;

    WeaponThunder *weapon_thunder_ = nullptr;
    SpriteAnim *sprite_idle_ = nullptr;
    SpriteAnim *sprite_move_ = nullptr;
    SpriteAnim *sprite_hurt_ = nullptr;
    SpriteAnim *cur_sprite_ = nullptr;

    Effect *death_effect_ = nullptr;


public:
    virtual void init() override;
    virtual void update(float dt) override;
    virtual void handleEvents(SDL_Event &event) override;
    virtual void render() override;
    virtual void clean() override;

    virtual void takeDamage(float damage) override;

    void keyboardControl();
    
    void syncCamera();
    void checkState();
    void changeState(PlayerState state);
    void checkIsDeath();

    // getters and setters
    
};

#endif // PLAYER_H