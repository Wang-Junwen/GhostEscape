#ifndef SCENE_TITLE_H
#define SCENE_TITLE_H

#include "core/scene.h"

class HUDButton;
class SceneTitle : public Scene
{
protected:
    SDL_FColor boundray_color_ = {0.5f, 0.5f, 0.5f, 1};
    float color_timer_ = 0;

    HUDButton *button_start_;
    HUDButton *button_credits_;
    HUDButton *button_quit_;
public:
    virtual void init() override;
    virtual void update(float dt) override;
    virtual void handleEvents(SDL_Event &event) override;
    virtual void render() override;
    virtual void clean() override;

private:
    void renderBackground();
    void updateColor();
    void checkButtonQuit();
};
#endif // SCENE_TITLE_H