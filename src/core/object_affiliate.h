#ifndef OBJECT_AFFILIATE_H
#define OBJECT_AFFILIATE_H

#include "object_screen.h"

class ObjectAffiliate : public Object
{
protected:
    ObjectScreen *parent_ = nullptr;     // 父节点
    glm::vec2 offset_ = glm::vec2(0.0f); // 相对于父节点的偏移位置
    glm::vec2 size_ = glm::vec2(0.0f);   // 尺寸

    Anchor anchor_ = Anchor::CENTER; // 锚点

public:
    void setOffsetFromAnchor(Anchor anchor);
    void setScale(float scale);

    // getters and setters
    ObjectScreen *getParent() const { return parent_; }
    void setParent(ObjectScreen *parent) { parent_ = parent; }
    glm::vec2 getOffset() const { return offset_; }
    void setOffset(const glm::vec2 &offset) { offset_ = offset; }
    glm::vec2 getSize() const { return size_; }
    void setSize(const glm::vec2 &size);
    Anchor getAnchor() const { return anchor_; }
    void setAnchor(Anchor anchor) { anchor_ = anchor; }
};

#endif // OBJECT_AFFILIATE_H