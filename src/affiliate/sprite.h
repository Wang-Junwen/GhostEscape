#ifndef SPRITE_H
#define SPRITE_H

#include "../core/object_affiliate.h"

struct TextureInfo
{
    SDL_Texture *texture = nullptr;    // SDL纹理指针
    SDL_FRect src_rect = {0, 0, 0, 0}; // 纹理源矩形
    float angle = 0;                   // 旋转角度
    bool is_flip = false;              // 是否水平翻转
    TextureInfo() = default;
    TextureInfo(const std::string &file_path);
};

class Sprite : public ObjectAffiliate
{
protected:
    TextureInfo texture_info_; // 纹理对象
    bool is_finish_ = false;    // 纹理是否加载完成
public:
    static Sprite *addSpriteChild(ObjectScreen *parent, const std::string &file_path, float scale = 1.0f);
    virtual void render() override;

    void setScale(float scale) {size_ *= scale; }

    // getters and setters
    TextureInfo getTextureInfo() { return texture_info_; }
    virtual void setTextureInfo(const TextureInfo &texture);
    void setFlip(bool is_flip) { texture_info_.is_flip = is_flip; }
    bool getFlip() { return texture_info_.is_flip; }
    void setAngle(float angle) { texture_info_.angle = angle; }
    float getAngle() { return texture_info_.angle; }
    void setFinish(bool finish) { is_finish_ = finish; }
    bool getFinish() { return is_finish_; }
};
#endif // SPRITE_H