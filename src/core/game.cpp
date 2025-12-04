#include "game.h"
#include "../scene_main.h"
#include "../scene_title.h"
#include "object_screen.h"
#include "object_world.h"
#include "actor.h"
#include "../affiliate/sprite.h"

void Game::run()
{

    while (is_running_)
    {
        auto start = SDL_GetTicksNS();
        if (next_scene_ != nullptr)
        {
            changeScene(next_scene_);
            next_scene_ = nullptr;
        }
        handleEvents();
        update(dt_);
        render();
        auto end = SDL_GetTicksNS();
        auto elapsed = end - start;
        if (elapsed < frame_delay_)
        {
            SDL_DelayNS(frame_delay_ - elapsed);
            dt_ = frame_delay_ / 1.0e9f;
        }
        else
        {
            dt_ = elapsed / 1.0e9f;
        }
    }
}

void Game::init(std::string title, int width, int height)
{
    screen_size_ = glm::vec2(width, height);
    // SDL3初始化
    if (!SDL_Init(SDL_INIT_AUDIO | SDL_INIT_VIDEO))
    {
        SDL_LogError(SDL_LOG_CATEGORY_ERROR, "SDL初始化失败: %s\n", SDL_GetError());
    }
    // 不需要进行SDL_image初始化
    // SDL3_Mixer初始化
    if (Mix_Init(MIX_INIT_MP3 | MIX_INIT_OGG) != (MIX_INIT_MP3 | MIX_INIT_OGG))
    {
        SDL_LogError(SDL_LOG_CATEGORY_ERROR, "SDL_Mixer初始化失败: %s\n", SDL_GetError());
    }
    if (!Mix_OpenAudio(0, NULL))
    {
        SDL_LogError(SDL_LOG_CATEGORY_ERROR, "SDL_Mixer音频打开失败: %s\n", SDL_GetError());
    }
    Mix_AllocateChannels(16);            // 分配16个音频通道
    Mix_VolumeMusic(MIX_MAX_VOLUME / 4); // 设置音乐音量
    Mix_Volume(-1, MIX_MAX_VOLUME / 4);  // 设置其他音效音量

    // SDL3_TTF初始化
    if (!TTF_Init())
    {
        SDL_LogError(SDL_LOG_CATEGORY_ERROR, "SDL_TTF初始化失败: %s\n", SDL_GetError());
    }

    // 创建窗口与渲染器
    SDL_CreateWindowAndRenderer(title.c_str(), width, height, SDL_WINDOW_RESIZABLE, &window_, &renderer_);
    if (!window_ || !renderer_)
    {
        SDL_LogError(SDL_LOG_CATEGORY_ERROR, "SDL窗口或渲染器创建失败: %s\n", SDL_GetError());
    }
    // 设置渲染器混合模式
    if (!SDL_SetRenderDrawBlendMode(renderer_, SDL_BLENDMODE_BLEND))
    {
        // 可选：打印错误信息
        SDL_LogError(SDL_LOG_CATEGORY_RENDER, "无法设置渲染器混合模式: %s\n", SDL_GetError());
    }
    // 设置窗口逻辑分辨率
    SDL_SetRenderLogicalPresentation(renderer_, width, height, SDL_LOGICAL_PRESENTATION_LETTERBOX);

    // TTF引擎
    ttf_engine_ = TTF_CreateRendererTextEngine(renderer_);

    // 计算帧延迟
    frame_delay_ = static_cast<Uint64>(1000000000.0f / FPS_); // ns

    // 创建资源管理器
    asset_store_ = new AssetStore(renderer_);

    // 创建场景
    current_scene_ = new SceneTitle();
    current_scene_->init();
}

void Game::handleEvents()
{
    SDL_Event event;
    while (SDL_PollEvent(&event))
    {
        switch (event.type)
        {
        case SDL_EVENT_QUIT:
            is_running_ = false;
            break;
        default:
            current_scene_->handleEvents(event);
        }
    }
}

void Game::update(float dt)
{
    updateMouse();
    current_scene_->update(dt);
}

void Game::render()
{
    SDL_SetRenderDrawColor(renderer_, 0, 0, 0, 255); // 为清屏操作准备颜色
    SDL_RenderClear(renderer_);                      // 清屏
    current_scene_->render();
    SDL_RenderPresent(renderer_); // 渲染
}

void Game::clean()
{
    // 清理当前场景
    if (current_scene_)
    {
        current_scene_->clean();
        delete current_scene_;
        current_scene_ = nullptr;
    }
    if (asset_store_)
    {
        asset_store_->clean();
        delete asset_store_;
        asset_store_ = nullptr;
    }
    // 释放字体引擎
    if (ttf_engine_)
    {
        TTF_DestroyRendererTextEngine(ttf_engine_);
    }
    // 释放渲染器和窗口
    if (renderer_)
    {
        SDL_DestroyRenderer(renderer_);
    }
    if (window_)
    {
        SDL_DestroyWindow(window_);
    }
    // 释放SDL_Mixer
    Mix_CloseAudio();
    Mix_Quit();
    // 释放SDL_TTF
    TTF_Quit();
    // 释放SDL
    SDL_Quit();
}

void Game::setScore(int score)
{
    score_ = score;
    setHighScore(score); // 更新最高分
}

void Game::addScore(int score)
{
    setScore(score_ + score);
}

void Game::changeScene(Scene *scene)
{
    if (current_scene_)
    {
        current_scene_->clean();
        delete current_scene_;
    }
    current_scene_ = scene;
    current_scene_->init();
}

void Game::renderTexture(const TextureInfo &texture_info, const glm::vec2 &position, const glm::vec2 &size, const glm::vec2 &mask)
{
    SDL_FRect srcRect = {
        texture_info.src_rect.x,
        texture_info.src_rect.y + texture_info.src_rect.h * (1 - mask.y),
        texture_info.src_rect.w * mask.x,
        texture_info.src_rect.h * mask.y};
    SDL_FRect dstRect = {
        position.x,
        position.y + size.y * (1 - mask.y),
        size.x * mask.x,
        size.y * mask.y};
    SDL_RenderTextureRotated(renderer_, texture_info.texture, &srcRect, &dstRect, texture_info.angle, nullptr, texture_info.is_flip ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE);
}

void Game::renderFillCircle(const glm::vec2 &position, const glm::vec2 &size, float alpha)
{
    auto texture = asset_store_->getTexture("assets/UI/circle.png");
    SDL_FRect dstRect = {position.x, position.y, size.x, size.y};
    SDL_SetTextureAlphaModFloat(texture, alpha);
    SDL_RenderTexture(renderer_, texture, nullptr, &dstRect);
}

void Game::renderFillRect(const glm::vec2 &position, const glm::vec2 &size, float alpha)
{
    SDL_FRect dstRect = {position.x, position.y, size.x, size.y};
    SDL_SetRenderDrawColorFloat(renderer_, 0.0f, 1.0f, 0, alpha);
    SDL_RenderFillRect(renderer_, &dstRect);
    SDL_SetRenderDrawColorFloat(renderer_, 0, 0, 0, 1.0f); // 恢复默认颜色
}

void Game::renderHBar(const glm::vec2 &position, const glm::vec2 &size, float percent, SDL_FColor color)
{
    // 设置颜色
    SDL_SetRenderDrawColorFloat(renderer_, color.r, color.g, color.b, color.a);
    // 绘制进度条外框
    SDL_FRect boundary_rect = {position.x, position.y, size.x, size.y};
    SDL_RenderRect(renderer_, &boundary_rect);

    // 计算进度条长度
    float bar_length = size.x * percent;
    // 绘制进度条
    SDL_FRect rect = {position.x, position.y, bar_length, size.y};
    SDL_RenderFillRect(renderer_, &rect);
    // 恢复默认颜色
    SDL_SetRenderDrawColorFloat(renderer_, 0, 0, 0, 1.0f);
}

TTF_Text *Game::createTTFText(const std::string &text, const std::string &font_path, int font_size)
{
    auto font = asset_store_->getFont(font_path, font_size);
    return TTF_CreateText(ttf_engine_, font, text.c_str(), 0);
}

bool Game::isMouseInRect(const glm::vec2 &top_left, const glm::vec2 &buttom_right)
{
    return mouse_pos_.x >= top_left.x && mouse_pos_.x <= buttom_right.x && mouse_pos_.y >= top_left.y && mouse_pos_.y <= buttom_right.y;
}

std::string Game::loadTextFile(const std::string &file_path)
{
    std::ifstream file(file_path);
    std::string line;
    std::string content;
    while (std::getline(file, line))
    {
        content += line + "\n";
    }
    return content;
}

void Game::updateMouse()
{   // 两种方法，保持系统鼠标和游戏鼠标一致性
    mouse_button_ = SDL_GetMouseState(&mouse_pos_.x, &mouse_pos_.y);
    // 1. 强制分辨率
    int w, h;
    SDL_GetWindowSize(window_, &w, &h);
    SDL_SetWindowAspectRatio(window_, screen_size_.x / screen_size_.y, screen_size_.x / screen_size_.y);
    mouse_pos_ *= screen_size_ / glm::vec2(w, h);

    // // 2. 保持黑边，转换鼠标位置
    // SDL_FRect rect;
    // SDL_GetRenderLogicalPresentationRect(renderer_, &rect);
    // mouse_pos_ = (mouse_pos_ - glm::vec2(rect.x, rect.y)) * screen_size_ / glm::vec2(rect.w, rect.h); // 将鼠标位置转换为屏幕坐标
}

void Game::drawGrid(const glm::vec2 &top_left, const glm::vec2 &bottom_right, float grid_width, SDL_FColor fcolor)
{
    SDL_SetRenderDrawColorFloat(renderer_, fcolor.r, fcolor.g, fcolor.b, fcolor.a);
    for (float x = top_left.x; x <= bottom_right.x; x += grid_width)
    {
        SDL_RenderLine(renderer_, x, top_left.y, x, bottom_right.y);
    }
    for (float y = top_left.y; y <= bottom_right.y; y += grid_width)
    {
        SDL_RenderLine(renderer_, top_left.x, y, bottom_right.x, y);
    }
    SDL_SetRenderDrawColorFloat(renderer_, 0, 0, 0, 1.0f); // 恢复默认颜色
}

void Game::drawBoundary(const glm::vec2 &top_left, const glm::vec2 &bottom_right, float boundary_width, SDL_FColor fcolor)
{
    SDL_SetRenderDrawColorFloat(renderer_, fcolor.r, fcolor.g, fcolor.b, fcolor.a);
    for (float i = 0; i < boundary_width; i += 1.0f)
    {
        SDL_FRect rect = {
            top_left.x - i,
            top_left.y - i,
            (bottom_right.x - top_left.x) + 2 * i,
            (bottom_right.y - top_left.y) + 2 * i};
        SDL_RenderRect(renderer_, &rect);
    }
    SDL_SetRenderDrawColorFloat(renderer_, 0, 0, 0, 1.0f); // 恢复默认颜色
}

void Game::drawPoints(const std::vector<glm::vec2> &points, glm::vec2 render_pos, SDL_FColor fcolor)
{
    SDL_SetRenderDrawColorFloat(renderer_, fcolor.r, fcolor.g, fcolor.b, fcolor.a);
    for (const auto &point : points)
    {
        SDL_RenderPoint(renderer_, render_pos.x + point.x, render_pos.y + point.y);
    }
    SDL_SetRenderDrawColorFloat(renderer_, 0, 0, 0, 1.0f); // 恢复默认颜色
}
