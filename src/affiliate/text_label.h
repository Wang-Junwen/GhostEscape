#ifndef TEXT_LABEL_H
#define TEXT_LABEL_H

#include "../core/object_affiliate.h"
#include <string>

class TextLabel : public ObjectAffiliate
{
protected:
    TTF_Text *ttf_text_ = nullptr;
    std::string font_path_;
    int font_size_ = 16;

public:
    static TextLabel *addTextLabelChild(ObjectScreen *parent, const std::string &text, const std::string &font_path, int font_size, Anchor anchor = Anchor::CENTER);
    virtual void render() override;
    virtual void clean() override;

    // getters and setters
    void setFont(const std::string &path, int size);
    std::string getFontPath() { return font_path_; }
    void setFontPath(const std::string &path);
    int getFontSize() { return font_size_; }
    void setFontSize(int size);
    void setText(const std::string text) { TTF_SetTextString(ttf_text_, text.c_str(), 0); }
    std::string getText() { return ttf_text_->text; }

private:
    void updateSize(); // 根据文字内容更新大小
};
#endif // TEXT_LABEL_H