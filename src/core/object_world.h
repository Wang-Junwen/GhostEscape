#ifndef OBJECT_WORLD_H
#define OBJECT_WORLD_H

#include "object_screen.h"

class ObjectWorld : public ObjectScreen
{
protected:
    glm::vec2 position_ = glm::vec2(0.0f); // 世界位置
    
public:
    virtual void init() override {type_ = ObjectType::OBJECT_WORLD;};
    virtual void update(float dt) override;
    // getters and setters
    glm::vec2 getPosition() const { return position_; }
    void setPosition(const glm::vec2 &pos);
    virtual void setRenderPosition(const glm::vec2 &pos) override;
};

#endif // OBJECT_WORLD_H