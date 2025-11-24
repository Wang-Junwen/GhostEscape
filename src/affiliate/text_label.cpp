#include "text_label.h"

TextLabel *TextLabel::addTextLabelChild(ObjectScreen *parent, const std::string &text, const std::string &font_path, int font_size, Anchor anchor)
{
    auto text_label = new TextLabel();
    text_label->init();
    text_label->setFont(font_path, font_size);
    text_label->setText(text);
    text_label->setAnchor(anchor);
    text_label->updateSize();
    if (parent)
    {
        parent->addChild(text_label);
        text_label->setParent(parent);
    }
    return text_label;
}

void TextLabel::render()
{
    ObjectAffiliate::render();
    auto pos = getRenderPosition();
    TTF_DrawRendererText(ttf_text_, pos.x, pos.y);
}

void TextLabel::clean()
{
    if (!ttf_text_)
        return;
    TTF_DestroyText(ttf_text_);
}

void TextLabel::setFont(const std::string &path, int size)
{
    font_size_ = size;
    font_path_ = path;
    auto font = game_.getAssetStore()->getFont(font_path_, font_size_);
    if (!ttf_text_) ttf_text_ = game_.createTTFText("", font_path_, font_size_);
    TTF_SetTextFont(ttf_text_, font);
}

void TextLabel::setFontPath(const std::string &path)
{
    font_path_ = path;
    auto font = game_.getAssetStore()->getFont(font_path_, font_size_);
    TTF_SetTextFont(ttf_text_, font);
}

void TextLabel::setFontSize(int size)
{
    font_size_ = size;
    auto font = game_.getAssetStore()->getFont(font_path_, font_size_);
    TTF_SetTextFont(ttf_text_, font);
}

void TextLabel::updateSize()
{
    int w, h;
    TTF_GetTextSize(ttf_text_, &w, &h);
    setSize(glm::vec2(w, h));
}
