#include "collider.h"

void Collider::render()
{
#ifdef DEBUG_MODE
    ObjectAffiliate::render();
    auto pos = parent_->getRenderPosition() + offset_;
    game_.renderFillCircle(pos, size_, 0.3f); // 半透明圆圈，用于表示碰撞体积
#endif                                        // DEBUG_MODE
}

Collider *Collider::addColliderChild(ObjectScreen *parent, const glm::vec2 &size, ColliderType type, Anchor anchor)
{
    Collider *collider = new Collider();
    collider->init();
    collider->setAnchor(anchor);
    collider->setParent(parent);
    collider->setSize(size);
    collider->setColliderType(type);
    parent->addChild(collider);
    return collider;
}

bool Collider::isColliding(const Collider &other)
{
    if (this->getColliderType() == ColliderType::CIRCLE && other.getColliderType() == ColliderType::CIRCLE)
    {
        // 获取圆心坐标
        auto center1 = this->getParent()->getPosition() + this->getOffset() + this->getSize() / 2.0f;
        auto center2 = other.getParent()->getPosition() + other.getOffset() + other.getSize() / 2.0f;

        // 比较两个圆心之间的距离 是否 小于 两个圆的半径之和
        return glm::length(center1 - center2) < (this->getSize().x + other.getSize().x) / 2.0f;
    }
    // TODO: 其他类型的碰撞检测
    return false;
}
