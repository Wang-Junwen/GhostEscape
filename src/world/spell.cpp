#include "spell.h"
#include "../core/scene.h"

Spell *Spell::addSpellChild(Object *parent, const std::string &file_path, glm::vec2 pos, float damage, float scale, Anchor anchor)
{
    auto spell = new Spell();
    spell->init();
    spell->sprite_ = SpriteAnim::addSpriteAnimChild(spell, file_path, scale, anchor);
    spell->collider_ = Collider::addColliderChild(spell, spell->sprite_->getSize(), ColliderType::CIRCLE, anchor);
    spell->sprite_->setLoop(false);
    spell->setPosition(pos);
    spell->damage_ = damage;
    if (parent)
        parent->addChild(spell);
    return spell;
}

void Spell::update(float dt)
{
    ObjectWorld::update(dt);
    if (sprite_->getFinish())
    {
        need_remove_ = true;
    }
    attack();
}

void Spell::attack()
{
    auto objects = game_.getCurrentScene()->getChildrenWorld();
    for (auto &obj : objects)
    {
        if (obj->getType() != ObjectType::ENEMY)
            continue;
        if (collider_ && obj->getCollider() && collider_->isColliding(*obj->getCollider()))
        {
            obj->takeDamage(damage_);
        }
    }
}
