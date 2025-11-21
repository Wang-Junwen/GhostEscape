#include "collider.h"

void Collider::render()
{
#ifdef DEBUG_MODE
    ObjectAffiliate::render();
    auto pos = parent_->getRenderPosition() + offset_;
    switch (collider_type_)
    {
    case ColliderType::CIRCLE:
        game_.renderFillCircle(pos, size_, 0.3f); // 半透明圆圈，用于表示碰撞体积
        break;
    case ColliderType::RECTANGLE:
        game_.renderFillRect(pos, size_, 0.3f);
        break;
    default:
        break;
    }
#endif // DEBUG_MODE
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
    // 两个圆形的碰撞检测
    if (this->getColliderType() == ColliderType::CIRCLE && other.getColliderType() == ColliderType::CIRCLE)
    {
        // 获取圆心坐标
        auto center1 = this->getParent()->getPosition() + this->getOffset() + this->getSize() / 2.0f;
        auto center2 = other.getParent()->getPosition() + other.getOffset() + other.getSize() / 2.0f;

        // 比较两个圆心之间的距离 是否 小于 两个圆的半径之和
        return glm::length(center1 - center2) < (this->getSize().x + other.getSize().x) / 2.0f;
    }
    // 矩形和圆形的碰撞检测
    else if ((this->getColliderType() == ColliderType::RECTANGLE && other.getColliderType() == ColliderType::CIRCLE) || 
    (this->getColliderType() == ColliderType::CIRCLE && other.getColliderType() == ColliderType::RECTANGLE))
    {
        // 获取圆心坐标
        auto center = this->getColliderType() == ColliderType::CIRCLE ? this->getParent()->getPosition() + this->getOffset() + this->getSize() / 2.0f : other.getParent()->getPosition() + other.getOffset() + other.getSize() / 2.0f;
        // 获取矩形四个顶点坐标
        auto rect = this->getColliderType() == ColliderType::RECTANGLE ? this : &other;
        auto rect_pos = rect->getParent()->getPosition() + rect->getOffset();
        auto rect_size = rect->getSize();
        // 判断矩形与圆形是否相交，核心逻辑是：找到矩形上离圆心最近的点，若该点到圆心的距离 ≤ 圆的半径，则两者相交（含相切、包含）
        auto point = glm::vec2(std::max(rect_pos.x, std::min(center.x, rect_pos.x + rect_size.x)), 
        std::max(rect_pos.y, std::min(center.y, rect_pos.y + rect_size.y)));
        return glm::length(center - point) <= this->getSize().x / 2.0f;
    }
    return false;
}
