#include "asset_store.h"

void AssetStore::clean()
{
    for (auto &pair : textures_) {
        SDL_DestroyTexture(pair.second);
    }
    textures_.clear();

    for (auto &pair : sounds_) {
        Mix_FreeChunk(pair.second);
    }
    sounds_.clear();

    for (auto &pair : musics_) {
        Mix_FreeMusic(pair.second);
    }
    musics_.clear();

    for (auto &pair : fonts_) {
        TTF_CloseFont(pair.second);
    }
    fonts_.clear();
    
}

void AssetStore::loadTexture(const std::string &path)
{
    SDL_Texture *texture = IMG_LoadTexture(renderer_, path.c_str());
    if (texture == nullptr) {
        SDL_LogError(SDL_LOG_CATEGORY_ERROR, "Failed to load texture: %s", path.c_str());
        return;
    }
    textures_.emplace(path, texture); // 如果已存在，则不会插入
}

void AssetStore::loadSound(const std::string &path)
{
    Mix_Chunk *chunk = Mix_LoadWAV(path.c_str());
    if (chunk == nullptr) {
        SDL_LogError(SDL_LOG_CATEGORY_ERROR, "Failed to load sound: %s", path.c_str());
        return;
    }
    sounds_.emplace(path, chunk);
}

void AssetStore::loadMusic(const std::string &path)
{
    Mix_Music *music = Mix_LoadMUS(path.c_str());
    if (music == nullptr) {
        SDL_LogError(SDL_LOG_CATEGORY_ERROR, "Failed to load music: %s", path.c_str());
        return;
    }
    musics_.emplace(path, music);
}

void AssetStore::loadFont(const std::string &path, int font_size)
{
    TTF_Font *font = TTF_OpenFont(path.c_str(), font_size);
    if (font == nullptr) {
        SDL_LogError(SDL_LOG_CATEGORY_ERROR, "Failed to load font: %s", path.c_str());
        return;
    }
    std::string key = path + "_" + std::to_string(font_size);
    fonts_.emplace(key, font);
}

SDL_Texture *AssetStore::getTexture(const std::string &path)
{
    auto it = textures_.find(path);
    if (it == textures_.end()) {
        loadTexture(path);
        it = textures_.find(path);
    }
    if (it == textures_.end()) {
        SDL_LogError(SDL_LOG_CATEGORY_ERROR, "Texture not found: %s", path.c_str());
        return nullptr;
    }
    return it->second;
}

Mix_Chunk *AssetStore::getSound(const std::string &path)
{
    auto it = sounds_.find(path);
    if (it == sounds_.end()) {
        loadSound(path);
        it = sounds_.find(path);
    }
    if (it == sounds_.end()) {
        SDL_LogError(SDL_LOG_CATEGORY_ERROR, "Sound not found: %s", path.c_str());
        return nullptr;
    }
    return it->second;
}

Mix_Music *AssetStore::getMusic(const std::string &path)
{
    auto it = musics_.find(path);
    if (it == musics_.end()) {
        loadMusic(path);
        it = musics_.find(path);
    }
    if (it == musics_.end()) {
        SDL_LogError(SDL_LOG_CATEGORY_ERROR, "Music not found: %s", path.c_str());
        return nullptr;
    }
    return it->second;
}

TTF_Font *AssetStore::getFont(const std::string &path, int font_size)
{
    std::string key = path + "_" + std::to_string(font_size);
    auto it = fonts_.find(key);
    if (it == fonts_.end()) {
        loadFont(path, font_size);
        it = fonts_.find(key);
    }
    if (it == fonts_.end()) {
        SDL_LogError(SDL_LOG_CATEGORY_ERROR, "Font not found: %s", path.c_str());
        return nullptr;
    }
    return it->second;
}
