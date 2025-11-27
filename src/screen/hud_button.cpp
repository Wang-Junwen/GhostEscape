#include "hud_button.h"

HUDButton *HUDButton::addHUDButtonChild(Object *parent, glm::vec2 render_pos, const std::string &normal_file_path, const std::string &hover_file_path, const std::string &pressed_file_path, float scale, Anchor anchor)
{
    auto hud_button = new HUDButton();
    hud_button->init();
    hud_button->setRenderPosition(render_pos);
    hud_button->sprite_normal_ = Sprite::addSpriteChild(hud_button, normal_file_path, scale, anchor);
    hud_button->sprite_hover_ = Sprite::addSpriteChild(hud_button, hover_file_path, scale, anchor);
    hud_button->sprite_pressed_ = Sprite::addSpriteChild(hud_button, pressed_file_path, scale, anchor);
    hud_button->sprite_normal_->setActive(true);
    hud_button->sprite_hover_->setActive(false);
    hud_button->sprite_pressed_->setActive(false);
    if (parent)
        parent->addChild(hud_button);
    return hud_button;
}

void HUDButton::update(float)
{
    checkHover();
    checkState();
}

bool HUDButton::handleEvents(SDL_Event &event)
{
    if (event.type == SDL_EVENT_MOUSE_BUTTON_DOWN)
    {
        if (event.button.button == SDL_BUTTON_LEFT)
        {
            if (getIsHover())
            {
                setPressed(true);
                game_.playSound("assets/sound/UI_button08.wav");
                return true;
            }
        }
    }
    else if (event.type == SDL_EVENT_MOUSE_BUTTON_UP)
    {
        if (event.button.button == SDL_BUTTON_LEFT)
        {
            if (getIsPressed())
            {
                setPressed(false);
                if (getIsHover())
                {
                    setTriggered(true);
                }
                return true;
            }
        }
    }
    return false;
}

void HUDButton::checkState()
{
    if (!getIsPressed() && !getIsHover())
    {
        sprite_normal_->setActive(true);
        sprite_hover_->setActive(false);
        sprite_pressed_->setActive(false);
    }
    else if (!getIsPressed() && getIsHover())
    {
        sprite_normal_->setActive(false);
        sprite_hover_->setActive(true);
        sprite_pressed_->setActive(false);
    }
    else
    {
        sprite_normal_->setActive(false);
        sprite_hover_->setActive(false);
        sprite_pressed_->setActive(true);
    }
}

void HUDButton::checkHover()
{
    auto pos = sprite_normal_->getRenderPosition();
    auto size = sprite_normal_->getSize();
    auto new_hover = game_.isMouseInRect(pos, pos + size);
    if (new_hover != getIsHover())
    {
        setHover(new_hover);
        if (getIsHover() && !getIsPressed())
        {
            game_.playSound("assets/sound/UI_button12.wav");
        }
    }
}

bool HUDButton::getIsTriggered()
{
    // 只触发一次，就会重置trigger状态
    if (is_triggered_)
    {
        is_triggered_ = false;
        return true;
    }
    return false;
}
