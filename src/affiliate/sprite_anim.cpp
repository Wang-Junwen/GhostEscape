#include "sprite_anim.h"

SpriteAnim *SpriteAnim::addSpriteAnimChild(ObjectScreen *parent, const std::string &file_path, float scale)
{
    auto sprite_anim = new SpriteAnim();
    sprite_anim->init();
    sprite_anim->setTextureInfo(TextureInfo(file_path)); // 设置纹理信息
    sprite_anim->setScale(scale);
    sprite_anim->setParent(parent);
    parent->addChild(sprite_anim); // 将精灵添加到父对象中
    return sprite_anim;
}

void SpriteAnim::update(float dt)
{
    frame_timer_ += dt;
    if (frame_timer_ >= 1.0f / fps_)
    {
        cur_frame_++;
        if (cur_frame_ >= total_frames_)
        {
            cur_frame_ = 0;
        }
        frame_timer_ = 0.0f;
    }
    texture_info_.src_rect.x = texture_info_.src_rect.w * cur_frame_;
}

void SpriteAnim::setTextureInfo(const TextureInfo &texture)
{
    texture_info_ = texture;
    total_frames_ = texture.src_rect.w / texture.src_rect.h;
    texture_info_.src_rect.w = texture.src_rect.h; // 每帧宽度等于高度
    size_ = glm::vec2(texture_info_.src_rect.w, texture_info_.src_rect.h);
}
