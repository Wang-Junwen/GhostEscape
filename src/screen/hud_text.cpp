#include "hud_text.h"

HUDText *HUDText::addHUDTextChild(Object *parent, const std::string &text, glm::vec2 renderPos, glm::vec2 size, const std::string &font_path, int font_size, const std::string &bg_path, Anchor anchor)
{
    auto hud_text = new HUDText();
    hud_text->init();
    hud_text->setRenderPosition(renderPos);
    hud_text->setSpriteBg(Sprite::addSpriteChild(hud_text, bg_path, 1, anchor));
    hud_text->setTextLabel(TextLabel::addTextLabelChild(hud_text, text, font_path, font_size, anchor));
    hud_text->setBgSize(size);
    hud_text->setText(text);
    if (parent)
        parent->addChild(hud_text);
    return hud_text;
}


void HUDText::setBgSize(const glm::vec2 &bg_size)
{
    bg_size_ = bg_size;
    sprite_bg_->setSize(bg_size);
}

void HUDText::setBackground(const std::string &file_path)
{
    if (sprite_bg_)
        sprite_bg_->setTextureInfo(file_path);
    else
        sprite_bg_ = Sprite::addSpriteChild(this, file_path, 1, Anchor::CENTER);
}
