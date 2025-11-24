#ifndef Game_h
#define Game_h

#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
#include <SDL3_mixer/SDL_mixer.h>
#include <SDL3_ttf/SDL_ttf.h>
#include <glm/glm.hpp>
#include <string>
#include <random>
#include "asset_store.h"

struct TextureInfo;
class Scene; // 前向声明，而不是引入scene.h头文件，防止循环引用等
// 单例模式
class Game
{
    AssetStore *asset_store_ = nullptr;     // 资源管理器
    glm::vec2 screen_size_ = glm::vec2(0);  // 屏幕尺寸
    glm::vec2 mouse_pos_ = glm::vec2(0);    // 鼠标位置
    SDL_MouseButtonFlags mouse_button_ = 0; // 鼠标按键状态
    bool is_running_ = true;                // 游戏是否运行
    Scene *current_scene_ = nullptr;        // 当前场景

    Uint64 FPS_ = 60;        // 帧率
    Uint64 frame_delay_ = 0; // 帧延迟, 单位ns, init中计算
    float dt_ = 0.0f;        // 每帧时间间隔, 单位s

    SDL_Window *window_ = nullptr;         // 窗口
    SDL_Renderer *renderer_ = nullptr;     // 渲染器
    TTF_TextEngine *ttf_engine_ = nullptr; // 字体引擎

    std::mt19937 gen_ = std::mt19937(std::random_device{}()); // 随机数生成器

    Game() {};
    Game(const Game &) = delete;
    Game &operator=(const Game &) = delete;

public:
    static Game &GetInstance()
    {
        static Game instance;
        return instance;
    };

    void run();                                          // 游戏主循环
    void init(std::string title, int width, int height); // 初始化游戏
    void handleEvents();                                 // 处理事件
    void update(float dt);                               // 更新游戏状态
    void render();                                       // 渲染游戏画面
    void clean();                                        // 清理游戏资源

    // getters and setters
    glm::vec2 getScreenSize() const { return screen_size_; }
    Scene *getCurrentScene() const { return current_scene_; }
    AssetStore *getAssetStore() const { return asset_store_; }
    glm::vec2 getMousePos() const { return mouse_pos_; }
    void setMousePos(glm::vec2 pos) { mouse_pos_ = pos; }
    SDL_MouseButtonFlags getMouseButton() const { return mouse_button_; }
    void setMouseButton(SDL_MouseButtonFlags button) { mouse_button_ = button; }

    // 随机数方法
    float randomFloat(float min, float max) { return std::uniform_real_distribution<float>(min, max)(gen_); }
    int randomInt(int min, int max) { return std::uniform_int_distribution<int>(min, max)(gen_); }
    glm::vec2 randomVec2(const glm::vec2 &min, const glm::vec2 &max) { return glm::vec2(randomFloat(min.x, max.x), randomFloat(min.y, max.y)); }
    glm::ivec2 randomIvec2(const glm::ivec2 &min, const glm::ivec2 &max) { return glm::ivec2(randomInt(min.x, max.x), randomInt(min.y, max.y)); }

    // 渲染函数
    void renderTexture(const TextureInfo &texture, const glm::vec2 &position, const glm::vec2 &size, const glm::vec2 &mask = glm::vec2(1.0f)); // 渲染纹理
    void renderFillCircle(const glm::vec2 &position, const glm::vec2 &size, float alpha);                                                      // 渲染实心圆
    void renderFillRect(const glm::vec2 &position, const glm::vec2 &size, float alpha);                                                        // 渲染实心矩形
    void renderHBar(const glm::vec2 &position, const glm::vec2 &size, float percent, SDL_FColor color);                                        // 渲染水平进度条

    // 文字函数
    TTF_Text* createTTFText(const std::string &text, const std::string &font_path, int font_size = 16); // 创建TTF文本

    // 工具函数
    void drawGrid(const glm::vec2 &top_left, const glm::vec2 &bottom_right, float grid_width, SDL_FColor fcolor);         // 绘制网格
    void drawBoundary(const glm::vec2 &top_left, const glm::vec2 &bottom_right, float boundary_width, SDL_FColor fcolor); // 绘制边界
};

#endif