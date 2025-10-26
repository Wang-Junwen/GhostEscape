#include "game.h"

void Game::run()
{
    
    while (is_running_){
        auto start = SDL_GetTicksNS();
        handleEvents();
        update(dt_);
        render();
        auto end = SDL_GetTicksNS();
        auto elapsed = end - start;
        if (elapsed < frame_delay_){
            SDL_DelayNS(frame_delay_ - elapsed);
            dt_ = frame_delay_ / 1.0e9f;
        }else{
            dt_ = elapsed / 1.0e9f;
        }

    }

}

void Game::init(std::string title, int width, int height)
{
    screen_size_ = glm::vec2(width, height);
    // SDL3初始化
    if (!SDL_Init(SDL_INIT_AUDIO | SDL_INIT_VIDEO)){
        SDL_LogError(SDL_LOG_CATEGORY_ERROR, "SDL初始化失败: %s\n", SDL_GetError());
    }
    // 不需要进行SDL_image初始化
    // SDL3_Mixer初始化
    if (Mix_Init(MIX_INIT_MP3 | MIX_INIT_OGG) != (MIX_INIT_MP3 | MIX_INIT_OGG)){
        SDL_LogError(SDL_LOG_CATEGORY_ERROR, "SDL_Mixer初始化失败: %s\n", SDL_GetError());
    }
    if (!Mix_OpenAudio(0, NULL)){
        SDL_LogError(SDL_LOG_CATEGORY_ERROR, "SDL_Mixer音频打开失败: %s\n", SDL_GetError());
    }
    Mix_AllocateChannels(16); //分配16个音频通道
    Mix_VolumeMusic(MIX_MAX_VOLUME / 4); //设置音乐音量
    Mix_Volume(-1, MIX_MAX_VOLUME / 4); //设置其他音效音量

    // SDL3_TTF初始化
    if (!TTF_Init()){
        SDL_LogError(SDL_LOG_CATEGORY_ERROR, "SDL_TTF初始化失败: %s\n", SDL_GetError());
    }

    // 创建窗口与渲染器
    SDL_CreateWindowAndRenderer(title.c_str(), width, height, SDL_WINDOW_RESIZABLE, &window_, &renderer_);
    if (!window_ || !renderer_){
        SDL_LogError(SDL_LOG_CATEGORY_ERROR, "SDL窗口或渲染器创建失败: %s\n", SDL_GetError());
    }
    // 设置窗口逻辑分辨率
    SDL_SetRenderLogicalPresentation(renderer_, width, height, SDL_LOGICAL_PRESENTATION_LETTERBOX);

    // 计算帧延迟
    frame_delay_ = static_cast<Uint64>(1000000000.0f / FPS_); // ns
}

void Game::handleEvents()
{
    SDL_Event event;
    while (SDL_PollEvent(&event)){
        switch (event.type){
        case SDL_EVENT_QUIT:
            is_running_ = false;
            break;
        default:
            break;
        }
    }
}

void Game::update(float dt)
{
}

void Game::render()
{
}

void Game::clean()
{
    // 释放渲染器和窗口
    if (renderer_){
        SDL_DestroyRenderer(renderer_);
    }
    if (window_){
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
