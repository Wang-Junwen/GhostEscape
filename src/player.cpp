#include "player.h"
#include "core/scene.h"
#include "affiliate/sprite_anim.h"

void Player::init()
{
    Actor::init(); // 调用父类初始化函数
    max_speed_ = 500.0f;
    sprite_idle_ = SpriteAnim::addSpriteAnimChild(this, "assets/sprite/ghost-idle.png", 2.0f);
    sprite_move_ = SpriteAnim::addSpriteAnimChild(this, "assets/sprite/ghost-move.png", 2.0f);
    sprite_move_->setActive(false); // 初始不显示移动动画
}

void Player::update(float dt)
{
    velocity_ *= 0.9f; // 惯性
    keyboardControl();
    checkState();
    move(dt);
    syncCamera();
    Actor::update(dt); // 调用父类更新函数
}

void Player::handleEvents(SDL_Event &event)
{
    Actor::handleEvents(event); // 调用父类事件处理函数
}

void Player::render()
{
    Actor::render(); // 调用父类渲染函数
}

void Player::clean()
{
    Actor::clean(); // 调用父类清理函数
}

void Player::keyboardControl()
{
    auto curKeyStates = SDL_GetKeyboardState(NULL);
    if (curKeyStates[SDL_SCANCODE_W])
    {
        velocity_.y = -max_speed_;
    }
    if (curKeyStates[SDL_SCANCODE_S])
    {
        velocity_.y = max_speed_;
    }
    if (curKeyStates[SDL_SCANCODE_A])
    {
        velocity_.x = -max_speed_;
    }
    if (curKeyStates[SDL_SCANCODE_D])
    {
        velocity_.x = max_speed_;
    }
    // 对角速度归一化
    if (glm::length(velocity_) > max_speed_)
    {
        velocity_ = glm::normalize(velocity_) * max_speed_;
    }
}

void Player::syncCamera()
{
    game_.getCurrentScene()->setCameraPos(position_ - game_.getScreenSize() / 2.0f);
}

void Player::checkState()
{
    if (velocity_.x < 0)
    {
        sprite_idle_->setFlip(true);
        sprite_move_->setFlip(true);
    }
    else
    {
        sprite_idle_->setFlip(false);
        sprite_move_->setFlip(false);
    }

    bool moving = (glm::length(velocity_) > 0.1f);
    if (moving != is_moving_)
    {
        is_moving_ = moving;
        changeState(moving); // 状态改变
    }
    
}

void Player::changeState(bool is_moving)
{
    if (is_moving)
    {
        sprite_idle_->setActive(false);
        sprite_move_->setActive(true);
        sprite_move_->setCurFrame(sprite_idle_->getCurFrame()); // 同步帧数
        sprite_move_->setFrameTimer(sprite_idle_->getFrameTimer()); // 同步计时器
    }
    else
    {
        sprite_idle_->setActive(true);
        sprite_move_->setActive(false);
        sprite_idle_->setCurFrame(sprite_move_->getCurFrame()); // 同步帧数
        sprite_idle_->setFrameTimer(sprite_move_->getFrameTimer()); // 同步计时器
    }
}
