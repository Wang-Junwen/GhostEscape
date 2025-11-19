#ifndef PLAYER_H
#define PLAYER_H

#include "core/actor.h"
#include "affiliate/sprite_anim.h"
#include "word/effect.h"

class Player : public Actor
{
    SpriteAnim *sprite_idle_ = nullptr;
    SpriteAnim *sprite_move_ = nullptr;
    Effect *death_effect_ = nullptr;
    bool is_moving_ = false;

public:
    virtual void init() override;
    virtual void update(float dt) override;
    virtual void handleEvents(SDL_Event &event) override;
    virtual void render() override;
    virtual void clean() override;

    void keyboardControl();
    
    void syncCamera();
    void checkState();
    void changeState(bool is_moving);
    void checkIsDeath();

    // getters and setters
    bool isMoving() const { return is_moving_; }
    void setMoving(bool is_moving) { is_moving_ = is_moving; }
};

#endif // PLAYER_H