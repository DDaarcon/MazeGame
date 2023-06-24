#pragma once

#include <memory>
#include <string>

#include <SFML/Graphics.hpp>

#include "TextureLoader.h"
#include "TextureType.h"
#include "TextureLoadData.h"


class TexturePack {
public:
    static void initializeSingleton(std::shared_ptr<ITextureLoader> loader);
    static std::shared_ptr<TexturePack> instance();


    std::shared_ptr<sf::Texture> getTexture(TextureType type);

    void loadOne(TextureType type, const std::string& path);
    void loadMany(std::vector<TextureLoadData> loadData);
   
    TexturePack(std::shared_ptr<ITextureLoader> loader);
private:

    static void ensureInitialized();

private:
    static std::shared_ptr<TexturePack> s_instance;

    std::shared_ptr<ITextureLoader> _loader;
    std::map<TextureType, std::shared_ptr<sf::Texture>> _storage;
};