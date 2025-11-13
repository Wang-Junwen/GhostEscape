#include "player.h"
#include "core/scene.h"

void Player::init()
{
    max_speed_ = 500.0f;
}

void Player::update(float dt)
{
    velocity_ *= 0.9f; // 惯性
    keyboardControl();
    move(dt);
    syncCamera();
}

void Player::handleEvents(SDL_Event &event)
{
}

void Player::render()
{
    game_.drawBoundary(render_position_, render_position_ + glm::vec2(20.0f), 5.0f, SDL_FColor{1.0f, 0.0f, 0.0f, 1.0f});
}

void Player::clean()
{
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
    auto pos_ = glm::clamp(position_ + velocity_ * dt, glm::vec2(0.0f), game_.getCurrentScene()->getWorldSize());     // 边界检测
    setPosition(pos_);
}

void Player::syncCamera()
{
    game_.getCurrentScene()->setCameraPos(position_ - game_.getScreenSize() / 2.0f);
}
