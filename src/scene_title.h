#ifndef SCENE_TITLE_H
#define SCENE_TITLE_H

#include "core/scene.h"

class HUDButton;
class HUDText;
class SceneTitle : public Scene
{
protected:
    SDL_FColor boundray_color_ = {0.5f, 0.5f, 0.5f, 1};
    float color_timer_ = 0;

    HUDButton *button_start_;
    HUDButton *button_credits_;
    HUDButton *button_quit_;
    HUDText *text_credits_;

public:
    virtual void init() override;
    virtual void update(float dt) override;
    virtual bool handleEvents(SDL_Event &event) override;
    virtual void render() override;
    virtual void clean() override;

    virtual void loadData(const std::string &file_path) override;

private:
    void renderBackground();
    void updateColor();
    void checkButtonQuit();
    void checkButtonStart();
    void checkButtonCredits();
};
#endif // SCENE_TITLE_H