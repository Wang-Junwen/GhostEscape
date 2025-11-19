#include "scene_main.h"
#include "player.h"
#include "enemy.h"
#include "world/effect.h"
#include "spawner.h"
#include "screen/ui_mouse.h"

void SceneMain::init()
{
    SDL_HideCursor();
    world_size_ = game_.getScreenSize() * 3.0f;                      // 世界尺寸为屏幕尺寸的三倍
    camera_pos_ = world_size_ / 2.0f - game_.getScreenSize() / 2.0f; // 相机位置

    player_ = new Player();
    player_->init();
    player_->setPosition(world_size_ / 2.0f); // 玩家初始位置在世界中心
    addChild(player_);

    spawner_ = new Spawner();
    spawner_->init();
    spawner_->setPlayer(player_);
    addChild(spawner_);

    ui_mouse_ = UIMouse::addUIMouseChild(this, "assets/UI/29.png", "assets/UI/30.png");
}

void SceneMain::update(float dt)
{
    Scene::update(dt);
}

void SceneMain::handleEvents(SDL_Event &event)
{
    Scene::handleEvents(event);
}

void SceneMain::render()
{
    renderBackground();
    Scene::render();
}

void SceneMain::clean()
{
    Scene::clean();
}

void SceneMain::renderBackground()
{
    // 绘制背景网格
    auto start = -camera_pos_;            // 起始位置
    auto end = world_size_ - camera_pos_; // 结束位置
    game_.drawGrid(
        start,
        end,
        80.0f,
        SDL_FColor{0.5f, 0.5f, 0.5f, 1.0f});
    // 绘制边框
    game_.drawBoundary(
        start,
        end,
        5.0f,
        SDL_FColor{1.0f, 1.0f, 1.0f, 1.0f});
}
