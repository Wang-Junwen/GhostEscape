#ifndef SPRITE_ANIM_H
#define SPRITE_ANIM_H

#include "sprite.h"

class SpriteAnim : public Sprite
{
    int cur_frame_ = 0;        // 当前帧
    int total_frames_ = 0;     // 总帧数
    int fps_ = 10;             // 帧率
    float frame_timer_ = 0.0f; // 帧计时器
    bool is_loop_ = true;    // 是否循环播放

public:
    static SpriteAnim *addSpriteAnimChild(ObjectScreen *parent, const std::string &file_path, float scale = 1.0f);
    virtual void update(float dt) override; // 更新动画

    // getters and setters
    virtual void setTextureInfo(const TextureInfo &texture) override;

    int getCurFrame() const { return cur_frame_; }
    void setCurFrame(int frame) { cur_frame_ = frame; }
    int getTotalFrames() const { return total_frames_; }
    void setTotalFrames(int total_frames) { total_frames_ = total_frames; }
    int getFps() const { return fps_; }
    void setFps(int fps) { fps_ = fps; }
    float getFrameTimer() const { return frame_timer_; }
    void setFrameTimer(float frame_timer) { frame_timer_ = frame_timer; }
    bool getLoop() const { return is_loop_; }
    void setLoop(bool is_loop) { is_loop_ = is_loop; }
};

#endif // SPRITE_ANIM_H