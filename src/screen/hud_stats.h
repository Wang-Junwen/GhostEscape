#ifndef HUD_STATS_H
#define HUD_STATS_H

#include "../core/object_screen.h"

class Sprite;
class Actor;
class HUDStats : public ObjectScreen
{
protected:
    Actor *target_ = nullptr;

    Sprite *health_bar_ = nullptr;
    Sprite *health_bar_bg_ = nullptr;
    Sprite *health_icon_ = nullptr;
    Sprite *mana_bar_ = nullptr;
    Sprite *mana_bar_bg_ = nullptr;
    Sprite *mana_icon_ = nullptr;

    float health_percentage_ = 1.0f;
    float mana_percentage_ = 1.0f;

public:
    static HUDStats *addHUDStatsChild(Object *parent, Actor *target, glm::vec2 render_pos);
    virtual void init() override;
    virtual void update(float dt) override;

    // getters and setters
    Actor *getTarget() const { return target_; }
    void setTarget(Actor *actor) { target_ = actor; }
    Sprite *getHealth_bar() const { return health_bar_; }
    Sprite *getHealth_bar_bg() const { return health_bar_bg_; }
    Sprite *getHealth_icon() const { return health_icon_; }
    Sprite *getMana_bar() const { return mana_bar_; }
    Sprite *getMana_bar_bg() const { return mana_bar_bg_; }
    Sprite *getMana_icon() const { return mana_icon_; }
    void setHealth_bar(Sprite *sprite) { health_bar_ = sprite; }
    void setHealth_bar_bg(Sprite *sprite) { health_bar_bg_ = sprite; }
    void setHealth_icon(Sprite *sprite) { health_icon_ = sprite; }
    void setMana_bar(Sprite *sprite) { mana_bar_ = sprite; }
    void setMana_bar_bg(Sprite *sprite) { mana_bar_bg_ = sprite; }
    void setMana_icon(Sprite *sprite) { mana_icon_ = sprite; }

    float getHealthPercentage() const { return health_percentage_; }
    float getManaPercentage() const { return mana_percentage_; }
    void setHealthPercentage(float percentage) { health_percentage_ = percentage; }
    void setManaPercentage(float percentage) { mana_percentage_ = percentage; }

private:
    void updateHealthBar();
    void updateManaBar();
};
#endif // HUD_STATS_H