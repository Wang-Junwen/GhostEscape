#include "bg_star.h"
#include "../core/game.h"
#include "../core/scene.h"

BGStar *BGStar::addBGStarChild(Object *parent, int num, float scale_far, float scale_mid, float scale_near)
{
    BGStar *bg_star = new BGStar();
    bg_star->num_ = num;
    bg_star->scale_far_ = scale_far;
    bg_star->scale_mid_ = scale_mid;
    bg_star->scale_near_ = scale_near;
    bg_star->stars_far_.reserve(num); // 预留空间以提高性能
    bg_star->stars_mid_.reserve(num);
    bg_star->stars_near_.reserve(num);
    auto extra = Game::GetInstance().getCurrentScene()->getWorldSize() - Game::GetInstance().getScreenSize(); // 额外渲染区域
    for (auto i = 0; i < num; ++i)
    {
        bg_star->stars_far_.push_back(Game::GetInstance().randomVec2(glm::vec2(0), Game::GetInstance().getScreenSize() + extra * scale_far));
        bg_star->stars_mid_.push_back(Game::GetInstance().randomVec2(glm::vec2(0), Game::GetInstance().getScreenSize() + extra * scale_mid));
        bg_star->stars_near_.push_back(Game::GetInstance().randomVec2(glm::vec2(0), Game::GetInstance().getScreenSize() + extra * scale_near));
    }

    if (parent)
        parent->addChild(bg_star);
    return bg_star;
}

void BGStar::update(float dt)
{
    // 更新颜色
    timer_ += dt;
    color_far_ = {0.5f + 0.5f * std::sinf(timer_ * 0.9f), 0.5f + 0.5f * std::sinf(timer_ * 0.8f), 0.5f + 0.5f * std::sinf(timer_ * 0.7f), 1.0f};
    color_mid_ = {0.5f + 0.5f * std::sinf(timer_ * 0.7f), 0.5f + 0.5f * std::sinf(timer_ * 0.8f), 0.5f + 0.5f * std::sinf(timer_ * 0.9f), 1.0f};
    color_near_ = {0.5f + 0.5f * std::sinf(timer_ * 0.6f), 0.5f + 0.5f * std::sinf(timer_ * 0.7f), 0.5f + 0.5f * std::sinf(timer_ * 0.8f), 1.0f};
}

void BGStar::render()
{
    game_.drawPoints(stars_far_, -game_.getCurrentScene()->getCameraPos() * scale_far_, color_far_);
    game_.drawPoints(stars_mid_, -game_.getCurrentScene()->getCameraPos() * scale_mid_, color_mid_);
    game_.drawPoints(stars_near_, -game_.getCurrentScene()->getCameraPos() * scale_near_, color_near_);
}
