#ifndef DEFS_H
#define DEFS_H

#define DEBUG_MODE

enum class ObjectType
{
    NONE,
    OBJECT_SCREEN,
    OBJECT_WORLD,
    ENEMY,
};

enum class ColliderType
{
    CIRCLE, // size_的x 表示直径， x=y
    RECTANGLE
};

enum class Anchor
{
    NONE,
    TOP_LEFT,
    TOP_CENTER,
    TOP_RIGHT,
    CENTER_LEFT,
    CENTER,
    CENTER_RIGHT,
    BOTTOM_LEFT,
    BOTTOM_CENTER,
    BOTTOM_RIGHT
};

#endif // DEFS_H