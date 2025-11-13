#include "player.h"
#include "core/scene.h"
#include "affiliate/sprite_anim.h"

void Player::init()
{
    Actor::init(); // 调用父类初始化函数
    max_speed_ = 500.0f;
    SpriteAnim::addSpriteAnimChild(this, "assets/sprite/ghost-idle.png", 2.0f);
}

void Player::update(float dt)
{
    Actor::update(dt); // 调用父类更新函数
    velocity_ *= 0.9f; // 惯性
    keyboardControl();
    move(dt);
    syncCamera();
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
}

void Player::move(float dt)
{
    auto pos_ = glm::clamp(position_ + velocity_ * dt, glm::vec2(0.0f), game_.getCurrentScene()->getWorldSize()); // 边界检测
    setPosition(pos_);
}

void Player::syncCamera()
{
    game_.getCurrentScene()->setCameraPos(position_ - game_.getScreenSize() / 2.0f);
}
