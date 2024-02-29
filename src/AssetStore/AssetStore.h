//
// Created by Konstantin Skrypak on 19.02.2024.
//

#pragma once

#include <SDL2/SDL.h>
#include <map>
#include <string>

class AssetStore {
private:
    std::map<std::string, SDL_Texture *> textures;
public:
    AssetStore();

    ~AssetStore();

    void ClearAssets();

    void AddTexture(SDL_Renderer *renderer, const std::string &assetId, const std::string &filePath);

    SDL_Texture *GetTexture(const std::string &assetId) const;
};


