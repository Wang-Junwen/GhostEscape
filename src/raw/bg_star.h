#ifndef BG_STAR_H
#define BG_STAR_H

#include "../core/object.h"

class BGStar : public Object
{
protected:
    std::vector<glm::vec2> stars_far_;
    std::vector<glm::vec2> stars_mid_;
    std::vector<glm::vec2> stars_near_;
    float scale_far_ = 0.2f;
    float scale_mid_ = 0.5f;
    float scale_near_ = 0.7f;
    SDL_FColor color_far_ = {0, 0, 0, 1.0f};
    SDL_FColor color_mid_ = {0, 0, 0, 1.0f};
    SDL_FColor color_near_ = {0, 0, 0, 1.0f};
    float timer_ = 0;
    int num_ = 2000; // 每一层星星的数量

public:
    static BGStar *addBGStarChild(Object *parent, int num, float scale_far, float scale_mid, float scale_near);
    virtual void update(float dt) override;
    virtual void render() override;

    // getters and setters
};

#endif // BG_STAR_H