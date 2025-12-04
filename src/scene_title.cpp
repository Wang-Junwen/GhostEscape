#include "scene_title.h"
#include "screen/hud_text.h"
#include "screen/hud_button.h"
#include "screen/ui_mouse.h"
#include "scene_main.h"
#include <cmath>
#include <fstream>

void SceneTitle::init()
{
    Scene::init();
    SDL_HideCursor();
    loadData("assets/score.dat");
    auto size = glm::vec2(game_.getScreenSize().x / 2, game_.getScreenSize().y / 3);
    HUDText::addHUDTextChild(this, "武 士 逃 生", game_.getScreenSize() / 2.0f - glm::vec2(0, 100), size, "assets/font/VonwaonBitmap-16px.ttf", 64);
    HUDText::addHUDTextChild(this, "最高分：" + std::to_string(game_.getHighScore()), game_.getScreenSize() / 2.0f + glm::vec2(0, 100), glm::vec2(200, 50), "assets/font/VonwaonBitmap-16px.ttf", 32);
    std::string text = game_.loadTextFile("assets/credits.txt");

    button_start_ = HUDButton::addHUDButtonChild(this, game_.getScreenSize() / 2.0f + glm::vec2(-200, 200), "assets/UI/A_Start1.png", "assets/UI/A_Start2.png", "assets/UI/A_Start3.png", 2.0f, Anchor::CENTER);
    button_credits_ = HUDButton::addHUDButtonChild(this, game_.getScreenSize() / 2.0f + glm::vec2(0, 200), "assets/UI/A_Credits1.png", "assets/UI/A_Credits2.png", "assets/UI/A_Credits3.png", 2.0f, Anchor::CENTER);
    button_quit_ = HUDButton::addHUDButtonChild(this, game_.getScreenSize() / 2.0f + glm::vec2(200), "assets/UI/A_Quit1.png", "assets/UI/A_Quit2.png", "assets/UI/A_Quit3.png", 2.0f, Anchor::CENTER);

    text_credits_ = HUDText::addHUDTextChild(this, text, game_.getScreenSize() / 2.0f, glm::vec2(500, 500), "assets/font/VonwaonBitmap-16px.ttf", 16);
    text_credits_->setBgSizeByText();
    text_credits_->setActive(false);

    ui_mouse_ = UIMouse::addUIMouseChild(this, "assets/UI/pointer_c_shaded.png", "assets/UI/pointer_c_shaded.png", 1.0f, Anchor::TOP_LEFT);
}

void SceneTitle::update(float dt)
{
    color_timer_ += dt;
    updateColor();
    if (text_credits_->getActive())
    {
        ui_mouse_->update(dt);
        return;
    }

    Scene::update(dt);
    checkButtonQuit();
    checkButtonStart();
    checkButtonCredits();
}

bool SceneTitle::handleEvents(SDL_Event &event)
{
    if (text_credits_->getActive())
    {
        if (event.type == SDL_EVENT_MOUSE_BUTTON_UP)
        {
            text_credits_->setActive(false);
            return true;
        }
    }
    return Scene::handleEvents(event);
}

void SceneTitle::render()
{
    renderBackground();
    Scene::render();
}

void SceneTitle::clean()
{
    Scene::clean();
}

void SceneTitle::loadData(const std::string &file_path)
{
    int high_score = 0;
    std::ifstream file(file_path, std::ios::binary);
    if (file.is_open())
    {
        // 读取最高分
        file.read(reinterpret_cast<char *>(&high_score), sizeof(high_score));

        file.close();
    }
    game_.setHighScore(high_score);
}

void SceneTitle::renderBackground()
{
    game_.drawBoundary(glm::vec2(30.0f), game_.getScreenSize() - glm::vec2(30.0f), 10.0f, boundray_color_);
}

void SceneTitle::updateColor()
{
    boundray_color_.r = 0.5f + 0.5f * sinf(color_timer_ * 0.9f);
    boundray_color_.g = 0.5f + 0.5f * sinf(color_timer_ * 0.7f);
    boundray_color_.b = 0.5f + 0.5f * sinf(color_timer_ * 0.5f);
}

void SceneTitle::checkButtonQuit()
{
    if (button_quit_->getIsTriggered())
    {
        game_.quit();
    }
}

void SceneTitle::checkButtonStart()
{
    if (button_start_->getIsTriggered())
    {
        game_.safeChangeScene(new SceneMain());
    }
}

void SceneTitle::checkButtonCredits()
{
    if (button_credits_->getIsTriggered())
    {
        text_credits_->setActive(true);
    }
}
