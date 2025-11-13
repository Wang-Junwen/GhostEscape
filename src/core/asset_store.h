#ifndef ASSET_STORE_H
#define ASSET_STORE_H

#include <unordered_map>
#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
#include <SDL3_mixer/SDL_mixer.h>
#include <SDL3_ttf/SDL_ttf.h>
#include <string>

class AssetStore
{
private:
    SDL_Renderer *renderer_ = nullptr;
    std::unordered_map<std::string, SDL_Texture *> textures_;
    std::unordered_map<std::string, Mix_Chunk *> sounds_;
    std::unordered_map<std::string, Mix_Music *> musics_;
    std::unordered_map<std::string, TTF_Font *> fonts_;

public:
    AssetStore(SDL_Renderer *renderer) { renderer_ = renderer; }
    ~AssetStore() = default;

    void clean();

    // 4个资源读取函数
    void loadTexture(const std::string &path);
    void loadSound(const std::string &path);
    void loadMusic(const std::string &path);
    void loadFont(const std::string &path, int font_size);

    // 4个资源获取函数
    SDL_Texture *getTexture(const std::string &path);
    Mix_Chunk *getSound(const std::string &path);
    Mix_Music *getMusic(const std::string &path);
    TTF_Font *getFont(const std::string &path, int font_size);
};

#endif // ASSET_STORE_H