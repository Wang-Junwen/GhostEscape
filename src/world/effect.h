#ifndef EFFECT_H
#define EFFECT_H

#include "../core/object_world.h"
#include "../affiliate/sprite_anim.h"
#include <string>

class Effect : public ObjectWorld
{
    SpriteAnim *sprite_ = nullptr;
    ObjectWorld *next_object_ = nullptr;

public:
    static Effect *addEffectChild(Object *parent, const std::string &file_path, glm::vec2 position, float scale = 1.0f, ObjectWorld *next_obj = nullptr);
    virtual void update(float dt) override;

    // getters and setters
    SpriteAnim *getSprite() const { return sprite_; }
    void setSprite(SpriteAnim *sprite) { sprite_ = sprite; }
    ObjectWorld *getNextObject() const { return next_object_; }
    void setNextObject(ObjectWorld *next) { next_object_ = next; }

private:
    void checkFinish();
};
#endif // EFFECT_H