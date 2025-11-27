#ifndef HUD_TEXT_H
#define HUD_TEXT_H

#include "../core/object_screen.h"
#include "../affiliate/sprite.h"
#include "../affiliate/text_label.h"

class HUDText : public ObjectScreen
{
protected:
    Sprite *sprite_bg_ = nullptr;
    TextLabel *text_label_ = nullptr;
    glm::vec2 bg_size_ = glm::vec2(0.0f, 0.0f);

public:
    static HUDText *addHUDTextChild(Object *parent, const std::string &text, glm::vec2 renderPos, glm::vec2 size, const std::string &font_path = "assets/font/VonwaonBitmap-16px.ttf", int font_size = 32, const std::string &bg_path = "assets/UI/Textfield_01.png", Anchor anchor = Anchor::CENTER);

    void setBgSizeByText(float margin = 50.0f);
    // setters and getters
    void setSpriteBg(Sprite *sprite_bg) { sprite_bg_ = sprite_bg; }
    void setTextLabel(TextLabel *text_label) { text_label_ = text_label; }
    Sprite *getSpriteBg() const { return sprite_bg_; }
    TextLabel *getTextLabel() const { return text_label_; }
    glm::vec2 getBgSize() const { return bg_size_; }
    void setBgSize(const glm::vec2 &bg_size);

    void setText(const std::string &text) { text_label_->setText(text); }
    std::string getText() const { return text_label_->getText(); }

    void setBackground(const std::string &file_path);
};

#endif // HUD_TEXT_H