#ifndef OBJECT_WORLD_H
#define OBJECT_WORLD_H

#include "object_screen.h"
#include "../affiliate/collider.h"

class ObjectWorld : public ObjectScreen
{
protected:
    glm::vec2 position_ = glm::vec2(0.0f); // 世界位置
    Collider *collider_ = nullptr;        // 碰撞器
    
public:
    virtual void init() override {type_ = ObjectType::OBJECT_WORLD;};
    virtual void update(float dt) override;
    virtual void takeDamage(float damage) {};
    // getters and setters
    glm::vec2 getPosition() const { return position_; }
    void setPosition(const glm::vec2 &pos);
    virtual void setRenderPosition(const glm::vec2 &pos) override;
    Collider *getCollider() const { return collider_; }
    void setCollider(Collider *collider) { collider_ = collider; }
};

#endif // OBJECT_WORLD_H