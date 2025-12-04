#ifndef SCENE_MAIN_H
#define SCENE_MAIN_H

#include "core/scene.h"

class Spawner;
class Player;
class UIMouse;
class HUDStats;
class HUDText;
class HUDButton;
class Timer;
class SceneMain : public Scene
{
    Player *player_ = nullptr;            // 玩家指针
    Spawner *spawner_ = nullptr;          // 敌机生成器指针
    UIMouse *ui_mouse_ = nullptr;         // 鼠标指针
    HUDStats *hud_stats_ = nullptr;       // 状态栏指针
    HUDText *hud_text_score_ = nullptr;   // 得分文字指针
    HUDButton *button_pause_ = nullptr;   // 暂停按钮指针
    HUDButton *button_restart_ = nullptr; // 重置按钮指针
    HUDButton *button_back_ = nullptr;    // 返回按钮指针
    Timer *end_timer_ = nullptr;              // 定时器指针

public:
    SceneMain() = default;
    virtual ~SceneMain() = default;

    virtual void init() override;
    virtual void update(float dt) override;
    virtual bool handleEvents(SDL_Event &event) override;
    virtual void render() override;
    virtual void clean() override;

private:
    void renderBackground();
    void updateScore();
    void checkButtonPause();
    void checkButtonRestart();
    void checkButtonBack();
    void checkEndTimer();
};

#endif // SCENE_MAIN_H