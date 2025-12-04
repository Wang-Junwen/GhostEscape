#ifndef HUD_BUTTON_H
#define HUD_BUTTON_H

#include "../core/object_screen.h"
#include "../affiliate/sprite.h"

class HUDButton : public ObjectScreen
{
protected:
    Sprite *sprite_normal_ = nullptr;
    Sprite *sprite_pressed_ = nullptr;
    Sprite *sprite_hover_ = nullptr;

    bool is_pressed_ = false;
    bool is_hover_ = false;
    bool is_triggered_ = false;

public:
    static HUDButton *addHUDButtonChild(Object *parent, glm::vec2 render_pos, const std::string &normal_file_path, const std::string &hover_file_path, const std::string &pressed_file_path, float scale = 1.0f, Anchor anchor = Anchor::CENTER);

    virtual void update(float) override;
    virtual bool handleEvents(SDL_Event &event) override;

    void checkState();
    void checkHover();

    // setter and getter
    void setSpriteNormal(Sprite *sprite) { sprite_normal_ = sprite; }
    void setSpritePressed(Sprite *sprite) { sprite_pressed_ = sprite; }
    void setSpriteHover(Sprite *sprite) { sprite_hover_ = sprite; }
    Sprite *getSpriteNormal() const { return sprite_normal_; }
    Sprite *getSpritePressed() const { return sprite_pressed_; }
    Sprite *getSpriteHover() const { return sprite_hover_; }
    bool getIsPressed() const { return is_pressed_; }
    bool getIsHover() const { return is_hover_; }
    bool getIsTriggered();
    void setTriggered(bool triggered) { is_triggered_ = triggered; }
    void setPressed(bool pressed) { is_pressed_ = pressed; }
    void setHover(bool hover) { is_hover_ = hover; }
    void setScale(float scale);
};
#endif // HUD_BUTTON_H