#include "player.h"
#include "core/scene.h"
#include "affiliate/sprite_anim.h"
#include "affiliate/collider.h"
#include "raw/stats.h"
#include "affiliate/text_label.h"

void Player::init()
{
    Actor::init(); // 调用父类初始化函数
    max_speed_ = 500.0f;
    sprite_idle_ = SpriteAnim::addSpriteAnimChild(this, "assets/sprite/samuri/IDLE-sheet.png", 2.0f);
    sprite_move_ = SpriteAnim::addSpriteAnimChild(this, "assets/sprite/samuri/RUN-sheet.png", 2.0f);
    sprite_hurt_ = SpriteAnim::addSpriteAnimChild(this, "assets/sprite/samuri/HURT-sheet.png", 2.0f);
    sprite_move_->setActive(false); // 初始不显示移动动画
    sprite_hurt_->setActive(false); // 初始不显示受伤动画
    cur_sprite_ = sprite_idle_;

    auto col_size = glm::vec2(sprite_idle_->getSize().x * 0.5f, sprite_idle_->getSize().y * 0.8f);
    collider_ = Collider::addColliderChild(this, col_size, ColliderType::RECTANGLE, Anchor::CENTER);
    stats_ = Stats::addStatsChild(this);

    death_effect_ = Effect::addEffectChild(
        nullptr,
        "assets/effect/1764.png",
        glm::vec2(0.0f),
        2.0f);
    weapon_thunder_ = WeaponThunder::addWeaponThunderChild(this, 2.0f, 40.0f);
}

void Player::update(float dt)
{
    velocity_ *= 0.9f; // 惯性
    keyboardControl();
    checkState();
    move(dt);
    syncCamera();
    checkIsDeath();

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
    PlayerState new_state;
    if (stats_->getInvincible())
    {
        new_state = PlayerState::HURT;
    }
    else if (glm::length(velocity_) > 20.0f)
    {
        new_state = PlayerState::MOVE;
    }
    else
    {
        new_state = PlayerState::IDLE;
    }
    if (new_state != cur_state_)
        changeState(new_state);
    cur_sprite_->setFlip(velocity_.x < 0);
}

void Player::changeState(PlayerState state)
{
    cur_sprite_->setActive(false);

    switch (state)
    {
    case PlayerState::IDLE:
        cur_sprite_ = sprite_idle_;
        break;
    case PlayerState::MOVE:
        cur_sprite_ = sprite_move_;
        break;
    case PlayerState::HURT:
        cur_sprite_ = sprite_hurt_;
        break;
    }
    cur_sprite_->setActive(true);
    cur_state_ = state;
}

void Player::checkIsDeath()
{
    if (!stats_->getAlive())
    {
        SDL_Log("Player is dead!");
        game_.getCurrentScene()->safeAddChild(death_effect_);
        death_effect_->setPosition(this->getPosition());
        setActive(false);
    }
}
