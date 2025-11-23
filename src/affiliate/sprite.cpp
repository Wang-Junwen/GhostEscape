#include "sprite.h"

TextureInfo::TextureInfo(const std::string &file_path)
{
    texture = Game::GetInstance().getAssetStore()->getTexture(file_path);
    SDL_GetTextureSize(texture, &src_rect.w, &src_rect.h);
}

Sprite *Sprite::addSpriteChild(ObjectScreen *parent, const std::string &file_path, float scale, Anchor anchor)
{
    auto sprite = new Sprite();
    sprite->init();
    sprite->setAnchor(anchor);
    sprite->setTextureInfo(TextureInfo(file_path)); // 设置纹理信息
    sprite->setScale(scale);
    sprite->setParent(parent);
    parent->addChild(sprite); // 将精灵添加到父对象中
    return sprite;
}

void Sprite::render()
{
    if (!texture_info_.texture || !parent_ || is_finish_) return;
    // 计算渲染位置，相对父节点偏移
    Game::GetInstance().renderTexture(texture_info_, getRenderPosition(), size_, percentage_); 
}

void Sprite::setTextureInfo(const TextureInfo &texture)
{
    texture_info_ = texture;
    size_ = glm::vec2(texture.src_rect.w, texture.src_rect.h);
}
