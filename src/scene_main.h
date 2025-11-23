#ifndef SCENE_MAIN_H
#define SCENE_MAIN_H

#include "core/scene.h"

class Spawner;
class Player;
class UIMouse;
class HUDStats;
class SceneMain : public Scene
{
    Player *player_ = nullptr;      // 玩家指针
    Spawner *spawner_ = nullptr;    // 敌机生成器指针
    UIMouse *ui_mouse_ = nullptr;   // 鼠标指针
    HUDStats *hud_stats_ = nullptr; // 状态栏指针
public:
    SceneMain() = default;
    virtual ~SceneMain() = default;

    virtual void init() override;
    virtual void update(float dt) override;
    virtual void handleEvents(SDL_Event &event) override;
    virtual void render() override;
    virtual void clean() override;

private:
    void renderBackground();
};

#endif // SCENE_MAIN_H