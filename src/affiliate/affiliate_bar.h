#ifndef AFFILIATE_BAR_H
#define AFFILIATE_BAR_H

#include "../core/object_affiliate.h"

class AffiliateBar : public ObjectAffiliate
{
protected:
    float percentage_ = 1.0f;
    SDL_FColor color_high = {0, 1, 0, 1};
    SDL_FColor color_mid = {1, 0.65f, 0, 1};
    SDL_FColor color_low = {1, 0, 0, 1};

public:
    static AffiliateBar *addAffiliateBarChild(ObjectScreen *parent, glm::vec2 size, Anchor anchor = Anchor::CENTER);
    virtual void render() override;

    // getters and setters
    float getPercentage() const { return percentage_; }
    void setPercentage(float percentage) { percentage_ = percentage; }
    SDL_FColor getColorHigh() const { return color_high; }
    void setColorHigh(SDL_FColor color) { color_high = color; }
    SDL_FColor getColorMid() const { return color_mid; }
    void setColorMid(SDL_FColor color) { color_mid = color; }
    SDL_FColor getColorLow() const { return color_low; }
    void setColorLow(SDL_FColor color) { color_low = color; }
};

#endif // AFFILIATE_BAR_H
