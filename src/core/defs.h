#ifndef DEFS_H
#define DEFS_H

#define DEBUG_MODE

enum class ObjectType
{
    NONE,
    OBJECT_SCREEN,
    OBJECT_WORLD,
};

enum class ColliderType
{
    CIRCLE, // size_的x 表示直径， x=y
    RECTANGLE
};

#endif // DEFS_H