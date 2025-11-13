#include "object_world.h"
#include "scene.h"

void ObjectWorld::update(float dt)
{
    ObjectScreen::update(dt); // 调用父类更新函数
    render_position_ = game_.getCurrentScene()->world2Screen(position_); // 更新渲染位置
}

void ObjectWorld::setPosition(const glm::vec2 &pos)
{
    position_ = pos;
    render_position_ = game_.getCurrentScene()->world2Screen(pos); // 同步更新渲染位置
}

void ObjectWorld::setRenderPosition(const glm::vec2 &pos)
{
    render_position_ = pos;
    position_ = game_.getCurrentScene()->screen2World(pos); // 同步更新世界位置
}
