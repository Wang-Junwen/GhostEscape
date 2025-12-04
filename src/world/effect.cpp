#include "effect.h"
#include "../core/scene.h"

Effect *Effect::addEffectChild(Object *parent, const std::string &file_path, glm::vec2 position, float scale, ObjectWorld *next_obj)
{
    auto effect = new Effect();
    effect->init();
    effect->setSprite(SpriteAnim::addSpriteAnimChild(effect, file_path, scale));
    effect->getSprite()->setLoop(false);
    effect->setPosition(position);
    effect->setNextObject(next_obj);
    if (parent)
        parent->addChild(effect);
    return effect;
}

void Effect::update(float dt)
{
    ObjectWorld::update(dt);
    checkFinish();
}

void Effect::clean()
{
    ObjectWorld::clean();
    if (next_object_)
    {
        next_object_->clean();
        delete next_object_;
        next_object_ = nullptr;
    }
}

void Effect::checkFinish()
{
    if (sprite_ && sprite_->getFinish())
    {
        this->setNeedRemove(true);
        if (next_object_)
        {
            game_.getCurrentScene()->safeAddChild(next_object_);
            next_object_ = nullptr; // 防止重复添加
        }
    }
}
