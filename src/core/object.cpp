#include "object.h"

void Object::update(float dt)
{
    for (auto child : children_)
    {
        if (child->isActive()){
            child->update(dt);
        }
    }
}

void Object::handleEvents(SDL_Event &event)
{
    for (auto child : children_)
    {
        if (child->isActive()){
            child->handleEvents(event);
        }
    }
}

void Object::render()
{
    for (auto child : children_)
    {
        if (child->isActive()){
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
