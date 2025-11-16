#ifndef COLLIDER_H
#define COLLIDER_H

#include "../core/object_affiliate.h"

class Collider : public ObjectAffiliate
{
protected:
    ColliderType collider_type_ = ColliderType::CIRCLE;

public:

    virtual void render() override;

    static Collider* addColliderChild(ObjectScreen *parent, const glm::vec2 &size, ColliderType type = ColliderType::CIRCLE)
    {
        Collider *collider = new Collider();
        collider->init();
        collider->setParent(parent);
        collider->setSize(size);
        collider->setColliderType(type);
        parent->addChild(collider);
        return collider;
    }

    bool isColliding(const Collider &other);

    // getters and setters
    ColliderType getColliderType() const { return collider_type_; }
    void setColliderType(ColliderType type) { collider_type_ = type; }
};

#endif // COLLIDER_H