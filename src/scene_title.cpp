#include "scene_title.h"
#include "screen/hud_text.h"
#include "screen/hud_button.h"
#include <cmath>

void SceneTitle::init()
{
    Scene::init();
    auto size = glm::vec2(game_.getScreenSize().x / 2, game_.getScreenSize().y / 3);
    HUDText::addHUDTextChild(this, "武 士 逃 生", game_.getScreenSize() / 2.0f - glm::vec2(0, 100), size, "assets/font/VonwaonBitmap-16px.ttf", 64);
    HUDText::addHUDTextChild(this, "最高分：" + std::to_string(game_.getHighScore()), game_.getScreenSize() / 2.0f + glm::vec2(0, 100), glm::vec2(200, 50), "assets/font/VonwaonBitmap-16px.ttf", 32);

    button_quit_ = HUDButton::addHUDButtonChild(this, game_.getScreenSize() / 2.0f + glm::vec2(200), "assets/UI/A_Quit1.png", "assets/UI/A_Quit3.png", "assets/UI/A_Quit2.png", 2.0f, Anchor::CENTER);
}

void SceneTitle::update(float dt)
{
    Scene::update(dt);
    color_timer_ += dt;
    updateColor();
    checkButtonQuit();
}

void SceneTitle::handleEvents(SDL_Event &event)
{
    Scene::handleEvents(event);
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
