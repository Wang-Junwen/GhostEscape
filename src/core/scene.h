#ifndef SCENE_H
#define SCENE_H

#include "object.h"
#include "object_world.h"
#include "object_screen.h"
#include <glm/glm.hpp>
#include <vector>

class Scene : public Object
{
protected:
    glm::vec2 camera_pos_ = glm::vec2(0.0f);      // 相机位置
    glm::vec2 world_size_ = glm::vec2(0);         // 世界尺寸
    std::vector<ObjectWorld *> children_world_;   // 世界子对象列表
    std::vector<ObjectScreen *> children_screen_; // 屏幕子对象列表

public:
    Scene() = default;
    virtual ~Scene() = default;

    virtual void init() override {};
    virtual void update(float dt) override;
    virtual void handleEvents(SDL_Event &event) override;
    virtual void render() override;
    virtual void clean() override;

    virtual void addChild(Object *child) override;    // 添加世界子对象
    virtual void removeChild(Object *child) override; // 移除世界子对象
    glm::vec2 world2Screen(const glm::vec2 &worldPos) const { return worldPos - camera_pos_; }
    glm::vec2 screen2World(const glm::vec2 &screenPos) const { return screenPos + camera_pos_; }

    // getters and setters
    glm::vec2 getCameraPos() const { return camera_pos_; }
    void setCameraPos(const glm::vec2 &pos);
    glm::vec2 getWorldSize() const { return world_size_; }
    void setWorldSize(const glm::vec2 &size) { world_size_ = size; }
};

#endif // SCENE_H