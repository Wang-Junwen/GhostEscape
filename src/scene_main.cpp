#include "scene_main.h"
#include "player.h"
#include "enemy.h"
#include "world/effect.h"
#include "spawner.h"
#include "screen/ui_mouse.h"
#include "world/spell.h"
#include "screen/hud_stats.h"
#include "screen/hud_text.h"
#include "screen/hud_button.h"
#include "scene_title.h"
#include "raw/timer.h"
#include "raw/bg_star.h"
#include <fstream>

void SceneMain::init()
{
    Scene::init();
    SDL_HideCursor();
    game_.playMusic("assets/bgm/OhMyGhost.ogg");
    world_size_ = game_.getScreenSize() * 3.0f;                      // 世界尺寸为屏幕尺寸的三倍
    camera_pos_ = world_size_ / 2.0f - game_.getScreenSize() / 2.0f; // 相机位置

    addChild(BGStar::addBGStarChild(this, 2000, 0.2f, 0.5f, 0.7f)); // 添加背景星空

    player_ = new Player();
    player_->init();
    player_->setPosition(world_size_ / 2.0f); // 玩家初始位置在世界中心
    addChild(player_);

    end_timer_ = Timer::addTimerChild(this); 

    spawner_ = new Spawner();
    spawner_->init();
    spawner_->setPlayer(player_);
    addChild(spawner_);

    hud_stats_ = HUDStats::addHUDStatsChild(this, player_, glm::vec2(30.0f));
    hud_text_score_ = HUDText::addHUDTextChild(this, "Score: 0", glm::vec2(game_.getScreenSize().x - 120.0f, 30.0f), glm::vec2(200.0f, 50.0f));

    button_pause_ = HUDButton::addHUDButtonChild(this, game_.getScreenSize() - glm::vec2(230.0f, 30.0f), "assets/UI/A_Pause1.png", "assets/UI/A_Pause2.png", "assets/UI/A_Pause3.png");
    button_restart_ = HUDButton::addHUDButtonChild(this, game_.getScreenSize() - glm::vec2(140.0f, 30.0f), "assets/UI/A_Restart1.png", "assets/UI/A_Restart2.png", "assets/UI/A_Restart3.png");
    button_back_ = HUDButton::addHUDButtonChild(this, game_.getScreenSize() - glm::vec2(50.0f, 30.0f), "assets/UI/A_Back1.png", "assets/UI/A_Back2.png", "assets/UI/A_Back3.png");

    // 鼠标UI最后添加，保持在最上层
    ui_mouse_ = UIMouse::addUIMouseChild(this, "assets/UI/29.png", "assets/UI/30.png");

    game_.setScore(0);
}

void SceneMain::update(float dt)
{
    Scene::update(dt);
    updateScore();
    checkButtonPause();
    checkButtonRestart();
    checkButtonBack();
    if (player_ && !player_->getActive()) {
        end_timer_->start();
    }
    checkEndTimer();
}

bool SceneMain::handleEvents(SDL_Event &event)
{
    return Scene::handleEvents(event);
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

void SceneMain::saveData(const std::string &file_path)
{
    std::ofstream file(file_path, std::ios::binary);
    if (file.is_open())
    {
        // 保存得分
        int score = game_.getScore();
        file.write(reinterpret_cast<const char *>(&score), sizeof(score));

        file.close();
    }
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

void SceneMain::updateScore()
{
    hud_text_score_->setText("Score: " + std::to_string(game_.getScore()));
}

void SceneMain::checkButtonPause()
{
    if (button_pause_->getIsTriggered())
    {
        if (getIsPause())
            resume();
        else
            pause();
    }
}

void SceneMain::checkButtonRestart()
{
    if (button_restart_->getIsTriggered())
    {
        saveData();
        game_.safeChangeScene(new SceneMain());
    }
}

void SceneMain::checkButtonBack()
{
    if (button_back_->getIsTriggered())
    {
        saveData();
        game_.safeChangeScene(new SceneTitle());
    }
}

void SceneMain::checkEndTimer()
{
    if (!end_timer_->timeOut()) return;
    pause();
    button_restart_->setRenderPosition(game_.getScreenSize() / 2.0f - glm::vec2(200.0f, 0.0f));
    button_restart_->setScale(4.0f);
    button_back_->setRenderPosition(game_.getScreenSize() / 2.0f + glm::vec2(200.0f, 0.0f));
    button_back_->setScale(4.0f);
    button_pause_->setActive(false);
    end_timer_->stop();
    saveData();
}

void SceneMain::saveData()
{
    saveData("assets/score.dat");
}
