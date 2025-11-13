#include "scene.h"

void Scene::setCameraPos(const glm::vec2 &pos)
{
    // camera_pos_ = pos;
    camera_pos_ = glm::clamp(pos, glm::vec2(-30.0f), world_size_ - game_.getScreenSize() + glm::vec2(30.0f));
}