#ifndef SCENE_MAIN_H
#define SCENE_MAIN_H

#include "core/scene.h"

class Player;
class SceneMain : public Scene
{
    
    Player *player_ = nullptr;            // 玩家指针
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