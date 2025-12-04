#include "object.h"

void Object::update(float dt)
{
    // 添加待添加的子对象
    for (auto &child_to_add : object_to_add_)
    {
        addChild(child_to_add);
    }
    object_to_add_.clear();

    for (auto it = children_.begin(); it != children_.end();)
    {
        auto child = *it;
        if (child->getNeedRemove())
        {
            it = children_.erase(it);
            child->clean();
            delete child;
            child = nullptr;
            continue;
        }

        if (child->getActive())
        {
            child->update(dt);
        }
        ++it;
    }
}

bool Object::handleEvents(SDL_Event &event)
{
    for (auto &child : children_)
    {
        if (child->getActive())
        {
            if (child->handleEvents(event))
                return true;
        }
    }
    return false;
}

void Object::render()
{
    for (auto &child : children_)
    {
        if (child->getActive())
        {
            child->render();
        }
    }
}

void Object::clean()
{
    for (auto &child : children_)
    {
        child->clean();
        delete child;
        child = nullptr;
    }
    children_.clear(); // delete all children
}
