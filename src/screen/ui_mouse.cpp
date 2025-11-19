#include "ui_mouse.h"

UIMouse *UIMouse::addUIMouseChild(Object *parent, const std::string &file_path1, const std::string &file_path2, float scale, Anchor anchor)
{
    UIMouse *ui_mouse = new UIMouse();
    ui_mouse->init();
    ui_mouse->sprite1_ = Sprite::addSpriteChild(ui_mouse, file_path1, scale, anchor);
    ui_mouse->sprite1_->setActive(false);
    ui_mouse->sprite2_ = Sprite::addSpriteChild(ui_mouse, file_path2, scale, anchor);
    ui_mouse->sprite2_->setActive(true);
    if (parent)
        parent->addChild(ui_mouse);
    return ui_mouse;
}

void UIMouse::update(float dt)
{
    timer_ += dt;
    if (timer_ > 0.3f)
    {
        timer_ = 0.0f;
        sprite1_->setActive(!sprite1_->getActive());
        sprite2_->setActive(!sprite2_->getActive());
    }
    setRenderPosition(game_.getMousePos());
}