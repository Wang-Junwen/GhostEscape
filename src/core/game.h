#ifndef Game_h
#define Game_h

#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
#include <SDL3_mixer/SDL_mixer.h>
#include <SDL3_ttf/SDL_ttf.h>
#include <glm/glm.hpp>
#include <string>

class Scene; // 前向声明，而不是引入scene.h头文件，防止循环引用等
// 单例模式
class Game
{  
    glm::vec2 screen_size_; // 屏幕尺寸
    bool is_running_ = true; // 游戏是否运行
    Scene* current_scene_ = nullptr; // 当前场景

    Uint64 FPS_ = 60; // 帧率
    Uint64 frame_delay_ = 0; // 帧延迟, 单位ns, init中计算
    float dt_ = 0.0f; // 每帧时间间隔, 单位s

    SDL_Window* window_ = nullptr; // 窗口
    SDL_Renderer* renderer_ = nullptr; // 渲染器

    Game(){};
    Game(const Game&) = delete;
    Game& operator=(const Game&) = delete;

public:
    static Game& GetInstance()
    {
        static Game instance;
        return instance;
    };

    void run(); // 游戏主循环
    void init(std::string title, int width, int height); // 初始化游戏
    void handleEvents(); // 处理事件
    void update(float dt); // 更新游戏状态
    void render(); // 渲染游戏画面
    void clean(); // 清理游戏资源
};

#endif