#include "object.h"

void Object::update(float dt)
{
    for (auto it = children_.begin(); it != children_.end();)
    {
        auto child = *it;
        if (child->getNeedRemove())
        {
            it = children_.erase(it);
            child->clean();
            SDL_Log("Object remove child: [%s]",typeid(*child).name());
            delete child;
            continue;
        }

        if (child->getActive())
        {
            child->update(dt);
        }
        ++it;
    }
}

void Object::handleEvents(SDL_Event &event)
{
    for (auto child : children_)
    {
        if (child->getActive())
        {
            child->handleEvents(event);
        }
    }
}

void Object::render()
{
    for (auto child : children_)
    {
        if (child->getActive())
        {
            child->render();
        }
    }
}

void Object::clean()
{
    for (auto child : children_)
    {
        child->clean();
    }
    children_.clear(); // delete all children
}
